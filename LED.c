#include "LED.h"
#include "key.h"

// System State Definitions (copied from empty.c for reference in LED logic)
/* 注意：为了解耦，这里使用数值或可以在头文件中共享枚举定义。
 * 简单起见，我们假设传入的 system_state 值为：
 * 0: STATE_NORMAL
 * 1: STATE_CALIB_BLACK
 * 2: STATE_CALIB_WHITE
 */
#define STATE_NORMAL      0
#define STATE_CALIB_BLACK 1
#define STATE_CALIB_WHITE 2

//自定义延时（不精确）
void delay_ms(unsigned int ms)
{
    unsigned int i, j;
    // 下面的嵌套循环的次数是根据主控频率和编译器生成的指令周期大致计算出来的，
    // 需要通过实际测试调整来达到所需的延时。
    for (i = 0; i < ms; i++)
    {
        for (j = 0; j < 8000; j++)
        {
            // 仅执行一个足够简单以致于可以预测其执行时间的操作
            __asm__("nop"); // "nop" 代表“无操作”，在大多数架构中，这会消耗一个或几个时钟周期
        }
    }
}

// 初始化LED数组，包含所有8个LED的端口和引脚信息
LED_T leds[] = {
    {LED_LED0_PORT, LED_LED0_PIN},
    {LED_LED1_PORT, LED_LED1_PIN},
    {LED_LED2_PORT, LED_LED2_PIN},
    {LED_LED3_PORT, LED_LED3_PIN},
    {LED_LED4_PORT, LED_LED4_PIN},
    {LED_LED5_PORT, LED_LED5_PIN},
    {LED_LED6_PORT, LED_LED6_PIN},
    {LED_LED7_PORT, LED_LED7_PIN}
};

// 初始化LED
void LED_init(void) {
    // LED引脚已通过SysConfig初始化，这里可以添加额外的初始化代码
}

// 运行LED流水灯
void LED_run_flow(void) {
    uint8_t i;
    
    // 正向流水灯：从LED0到LED7依次点亮
    for (i = 0; i < 8; i++) {
        DL_GPIO_setPins(leds[i].port, leds[i].pin);  // 点亮当前LED
        delay_ms(1000);  // 延迟1000ms
        DL_GPIO_clearPins(leds[i].port, leds[i].pin);  // 熄灭当前LED
    }
    
    // 反向流水灯：从LED7到LED0依次点亮
    for (i = 7; i > 0; i--) {
        DL_GPIO_setPins(leds[i].port, leds[i].pin);  // 点亮当前LED
        delay_ms(1000);  // 延迟1000ms
        DL_GPIO_clearPins(leds[i].port, leds[i].pin);  // 熄灭当前LED
    }
}

void LED_set(uint8_t index, uint8_t state) {
    if (index >= 8) return;
    if (state) {
        DL_GPIO_setPins(leds[index].port, leds[index].pin);
    } else {
        DL_GPIO_clearPins(leds[index].port, leds[index].pin);
    }
}

void LED_update(uint32_t system_state, uint32_t *avg, uint32_t *white_threshold, uint32_t *black_threshold) {
    if (system_state == STATE_NORMAL) {
        /* Real-time detection */
        for (int i = 0; i < 8; i++) {
            if (avg[i] >= white_threshold[i]) {
                LED_set(i, 0);
            } else if (avg[i] <= black_threshold[i]) {
                LED_set(i, 1);
            }
            /* Hysteresis: Keep previous state if in between */
        }
    } else {
        /* Calibration Mode: Flash LEDs */
        uint32_t tick = key_get_tick();
        
        if (system_state == STATE_CALIB_BLACK) {
            /* 黑色校准：所有LED同步闪烁 */
            /* 500ms周期：250ms亮，250ms灭 */
            uint8_t state = (tick % 1000) < 500 ? 1 : 0;
            for (int i = 0; i < 8; i++) {
                LED_set(i, state);
            }
        } else if (system_state == STATE_CALIB_WHITE) {
            /* 白色校准：流水灯效果 */
            /* 设定每个LED点亮时间为100ms，8个LED循环周期为800ms */
            int active_index = (tick / 100) % 8;
            for (int i = 0; i < 8; i++) {
                if (i == active_index) {
                    LED_set(i, 1);
                } else {
                    LED_set(i, 0);
                }
            }
        } else {
            /* 其他状态：熄灭所有LED */
            for (int i = 0; i < 8; i++) {
                LED_set(i, 0);
            }
        }
    }
}

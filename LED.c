#include "LED.h"

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

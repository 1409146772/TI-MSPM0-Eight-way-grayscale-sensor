#include "key.h"
#include "ti_msp_dl_config.h"
#include <ti/driverlib/driverlib.h>

/* 
 * 配置参数说明：
 * 假设 KEY_TIMER_1_INST 定时器中断周期配置为 1ms。
 * 如果实际中断周期不同，请相应调整以下宏定义。
 */
#define KEY_DEBOUNCE_TIME_MS      20   // 消抖时间 20ms
#define KEY_LONG_PRESS_TIME_MS    800  // 长按判定时间 800ms
#define KEY_SHORT_PRESS_MAX_MS    500  // 短按最大有效时间 500ms

/* 按键状态定义 */
typedef enum {
    KEY_STATE_IDLE = 0,       // 空闲状态
    KEY_STATE_DEBOUNCE,       // 消抖确认中
    KEY_STATE_PRESSED,        // 已确认按下，正在计时
    KEY_STATE_LONG_PRESS_HOLD // 长按触发后保持状态
} KeyState_t;

/* 按键控制块结构 */
typedef struct {
    GPIO_Regs *port;          // GPIO端口基地址
    uint32_t pin;             // GPIO引脚掩码
    KeyState_t state;         // 当前按键状态
    uint32_t tick;            // 状态计时器 (单位: ms)
    KeyCallback_t callback;   // 事件回调函数
} KeyControl_t;

/* 按键实例管理数组 */
static KeyControl_t gKeyControls[KEY_ID_MAX] = {
    /* KEY_ID_B1 */
    [KEY_ID_B1] = { 
        .port = KEY_B1_PORT, 
        .pin = KEY_B1_PIN, 
        .state = KEY_STATE_IDLE, 
        .tick = 0, 
        .callback = NULL 
    },
    /* KEY_ID_B2 */
    [KEY_ID_B2] = { 
        .port = KEY_B2_PORT, 
        .pin = KEY_B2_PIN, 
        .state = KEY_STATE_IDLE, 
        .tick = 0, 
        .callback = NULL 
    }
};

/* Global system tick counter */
/* 全局系统毫秒计数器，在定时器中断中递增 */
volatile uint32_t g_system_tick = 0;

/**
 * @brief 获取系统当前运行时间（毫秒）
 */
uint32_t key_get_tick(void)
{
    return g_system_tick;
}

/**
 * @brief 初始化按键模块
 */
void key_init(void)
{
    /* 开启定时器计数器 */
    DL_Timer_startCounter(KEY_TIMER_1_INST);
    /* 使能定时器中断 */
    NVIC_EnableIRQ(KEY_TIMER_1_INST_INT_IRQN);

    
}

/**
 * @brief 注册按键回调函数
 */
void key_register_callback(KeyId_t key_id, KeyCallback_t cb)
{
    if (key_id < KEY_ID_MAX) {
        gKeyControls[key_id].callback = cb;
    }
}

/**
 * @brief 定时器中断服务程序
 * 处理按键消抖、状态转换和事件触发
 */
void KEY_TIMER_1_INST_IRQHandler(void)
{
    switch (DL_Timer_getPendingInterrupt(KEY_TIMER_1_INST)) {
        case DL_TIMER_IIDX_ZERO:
            g_system_tick++; /* 系统Tick计数递增 (1ms) */
            /* 遍历所有注册的按键 */
            for (int i = 0; i < KEY_ID_MAX; i++) {
                KeyControl_t *key = &gKeyControls[i];
                /* 读取按键物理状态 (假设低电平有效) */
                bool is_pressed_now = (DL_GPIO_readPins(key->port, key->pin) == 0);

                switch (key->state) {
                    case KEY_STATE_IDLE:
                        if (is_pressed_now) {
                            /* 检测到按下，进入消抖状态 */
                            key->state = KEY_STATE_DEBOUNCE;
                            key->tick = 0;
                        }
                        break;

                    case KEY_STATE_DEBOUNCE:
                        if (is_pressed_now) {
                            key->tick++;
                            /* 持续按下达到消抖时间，确认按下 */
                            if (key->tick >= KEY_DEBOUNCE_TIME_MS) {
                                key->state = KEY_STATE_PRESSED;
                                key->tick = 0; // 重置计时器，开始计算按下时长
                            }
                        } else {
                            /* 未达到消抖时间即释放，视为抖动，重置为空闲 */
                            key->state = KEY_STATE_IDLE;
                        }
                        break;

                    case KEY_STATE_PRESSED:
                        if (is_pressed_now) {
                            key->tick++;
                            /* 按下时间超过长按阈值，触发长按事件 */
                            if (key->tick >= KEY_LONG_PRESS_TIME_MS) {
                                if (key->callback) {
                                    key->callback(KEY_EVENT_LONG_PRESS);
                                }
                                key->state = KEY_STATE_LONG_PRESS_HOLD;
                            }
                        } else {
                            /* 按键释放 */
                            if (key->tick < KEY_SHORT_PRESS_MAX_MS) {
                                /* 按下时间在短按范围内，触发短按事件 */
                                if (key->callback) {
                                    key->callback(KEY_EVENT_SHORT_PRESS);
                                }
                            }
                            /* 超过短按时间但未达长按时间，或长按已触发过，直接回空闲 */
                            key->state = KEY_STATE_IDLE;
                        }
                        break;

                    case KEY_STATE_LONG_PRESS_HOLD:
                        /* 等待按键释放，避免重复触发 */
                        if (!is_pressed_now) {
                            key->state = KEY_STATE_IDLE;
                        }
                        break;
                }
            }
            break;
            
        default:
            break;
    }
}

#ifndef LED_H
#define LED_H

#include "ti_msp_dl_config.h"

// 定义LED的端口和引脚结构
typedef struct {
    GPIO_Regs *port;
    uint32_t pin;
} LED_T;

// 初始化LED
void LED_init(void);

// 运行LED流水灯
void LED_run_flow(void);

// Set LED state (1: ON, 0: OFF)
/* 设置指定LED的状态 (1: 亮, 0: 灭) */
void LED_set(uint8_t index, uint8_t state);

/**
 * @brief 更新LED状态
 * 
 * 根据当前系统状态控制LED显示：
 * 1. 正常模式：根据ADC值与阈值的比较结果点亮/熄灭LED（带迟滞控制）。
 * 2. 校准模式：所有LED以500ms周期同步闪烁。
 * 
 * @param system_state 当前系统状态 (正常/黑校准/白校准)
 * @param avg 当前8路ADC平均值数组
 * @param white_threshold 8路白色阈值数组
 * @param black_threshold 8路黑色阈值数组
 */
void LED_update(uint32_t system_state, uint32_t *avg, uint32_t *white_threshold, uint32_t *black_threshold);

void delay_ms(unsigned int ms);

#endif /* LED_H */
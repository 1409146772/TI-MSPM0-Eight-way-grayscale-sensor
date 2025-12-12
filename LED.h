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

void delay_ms(unsigned int ms);

#endif /* LED_H */
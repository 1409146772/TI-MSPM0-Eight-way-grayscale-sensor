/*
 * Copyright (c) 2021, Texas Instruments Incorporated
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * *  Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 * *  Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * *  Neither the name of Texas Instruments Incorporated nor the names of
 *    its contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 * OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include "ti_msp_dl_config.h"

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


int main(void)
{
    SYSCFG_DL_init();

    // 定义LED的端口和引脚结构
    typedef struct {
        GPIO_Regs *port;
        uint32_t pin;
    } LED_T;

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

    uint8_t i;
    
    while (1) {
        // 正向流水灯：从LED0到LED7依次点亮
        for (i = 0; i < 8; i++) {
            DL_GPIO_setPins(leds[i].port, leds[i].pin);  // 点亮当前LED
            delay_ms(1000);  // 延迟100ms
            DL_GPIO_clearPins(leds[i].port, leds[i].pin);  // 熄灭当前LED
        }
        
        // 反向流水灯：从LED7到LED0依次点亮
        for (i = 7; i > 0; i--) {
            DL_GPIO_setPins(leds[i].port, leds[i].pin);  // 点亮当前LED
            delay_ms(1000);  // 延迟100ms
            DL_GPIO_clearPins(leds[i].port, leds[i].pin);  // 熄灭当前LED
        }
    }
}

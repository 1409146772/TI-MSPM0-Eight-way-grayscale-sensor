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
#include "LED.h"
#include <stdint.h>
#include <stdio.h>

/* Redirect stdio output to UART0 (blocking, no CRLF translation) */
int fputc(int c, FILE *f)
{
    (void)f;
    DL_UART_Main_transmitDataBlocking(UART_0_INST, (uint8_t)c);
    return c;
}

int fputs(const char *s, FILE *f)
{
    (void)f;
    while (*s) {
        DL_UART_Main_transmitDataBlocking(UART_0_INST, (uint8_t)(*s++));
    }
    return 0;
}

int puts(const char *s)
{
    int rc = fputs(s, stdout);
    fputc('\n', stdout);
    return rc;
}

uint16_t gADCSamples[2400];
uint32_t avg[8];
char flag=0;
int main(void)
{
    SYSCFG_DL_init();

    /* Configure DMA source, destination and size */
    DL_DMA_setSrcAddr(DMA, DMA_CH0_CHAN_ID,
        (uint32_t) DL_ADC12_getFIFOAddress(ADC12_0_INST));
    DL_DMA_setDestAddr(DMA, DMA_CH0_CHAN_ID, (uint32_t) &gADCSamples[0]);

    DL_DMA_enableChannel(DMA, DMA_CH0_CHAN_ID);

    /* Setup interrupts on device */
    NVIC_EnableIRQ(ADC12_0_INST_INT_IRQN);

    /* Reset FIFO to ensure no stale data */
    DL_ADC12_disableFIFO(ADC12_0_INST);
    DL_ADC12_enableFIFO(ADC12_0_INST);



    while (1) {
         for (uint32_t ch = 0; ch < 8; ch++) {
                printf("CH%lu avg=%lu\r\n", (unsigned long)ch, (unsigned long)avg[ch]);
         }

    }
}

void ADC12_0_INST_IRQHandler(void)
{
    switch (DL_ADC12_getPendingInterrupt(ADC12_0_INST)) {
        case DL_ADC12_IIDX_DMA_DONE:
            DL_TimerA_stopCounter(TIMER_0_INST);

            const uint32_t total = 480;
            const uint32_t channels = 8;
            const uint32_t per_channel = total / channels;
            uint32_t sum[8] = {0};
            for (uint32_t i = 0; i < total; i++) {
                sum[i % channels] += gADCSamples[i];
            }
            for (uint32_t ch = 0; ch < channels; ch++) {
                avg[ch] = sum[ch] / per_channel;
            }
           
           
           
            /* 重新设置Timer计数值，以调整采样间隔 */
            DL_TimerA_setLoadValue(TIMER_0_INST, TIMER_0_INST_LOAD_VALUE); 
            DL_TimerA_startCounter(TIMER_0_INST);
            break;
        default:
            break;
    }
}


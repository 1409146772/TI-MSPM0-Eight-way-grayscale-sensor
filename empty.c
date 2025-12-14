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

    //DL_ADC12_startConversion(ADC12_0_INST);

    
    //printf("UART0 printf redirect ready\n");

    while (1) {
        /* 打印gADCSamples的前八个数据 */
        // for (uint8_t i = 0; i < 8; i++) {
        //         printf("gADCSamples[%d] = %d\r\n", i, gADCSamples[i]);
        // }
        
        //delay_ms(1000);
    }
}

void ADC12_0_INST_IRQHandler(void)
{
    switch (DL_ADC12_getPendingInterrupt(ADC12_0_INST)) {
        case DL_ADC12_IIDX_DMA_DONE:
            //DL_ADC12_disableConversions(ADC12_0_INST);
            DL_TimerA_stopCounter(TIMER_0_INST);
            // for (uint32_t i = 0; i < 8; i++) {
            //     printf("gADCSamples[%d] = %d\r\n", i, gADCSamples[i]);
            // }
            flag=1;

            DL_TimerA_startCounter(TIMER_0_INST);
            // DL_ADC12_enableConversions(ADC12_0_INST);
            // DL_ADC12_startConversion(ADC12_0_INST);
            break;
        default:
            break;
    }
}


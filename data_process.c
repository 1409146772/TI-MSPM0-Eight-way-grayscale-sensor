#include "data_process.h"
#include "ti_msp_dl_config.h"
#include <stdio.h>
#include <stdint.h>

extern volatile uint32_t flag;
extern uint16_t gADCSamples[1000];
extern uint32_t avg[8];

void process_avg_and_restart_timer(void)
{
    flag=0;
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
    /* 
     * 禁用 printf 以提高实时性。
     * 在高频中断或高速数据处理中，UART打印会消耗大量时间，可能导致数据丢失或系统响应变慢。
     */
    /*
    for (uint32_t ch = 0; ch < 8; ch++) {
        printf("CH%lu avg=%lu\r\n", (unsigned long)ch, (unsigned long)avg[ch]);
    }
    */
    DL_TimerA_setLoadValue(TIMER_0_INST, TIMER_0_INST_LOAD_VALUE); 
    DL_TimerA_startCounter(TIMER_0_INST);
}

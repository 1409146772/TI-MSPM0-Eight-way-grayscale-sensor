
/* 设备配置与驱动头文件 */
#include "ti_msp_dl_config.h"   /* 设备驱动库配置与外设句柄 */
#include "LED.h"                /* 可选：LED 指示相关 */
#include "UART.h"               /* 可选：UART 打印与通信相关 */
#include "eeprom_emulation_type_b.h"

/* 标准库头文件 */
#include <stdint.h>             /* 标准整型定义 */
#include <stdio.h>              /* 标准输入输出，用于调试打印 */

/* 工程模块头文件 */
#include "data_process.h"       /* 数据处理函数声明 */
#include "key.h"

/* =========================
 * 全局变量区域
 * 说明：这些变量会被 DMA/中断/主循环共同访问，
 *      因此需保证作用域在整个工程可见（由 data_process.c 通过 extern 引用）。
 * ========================= */
uint16_t gADCSamples[1000];     /* ADC 采样数据缓冲区（DMA 写入），大小至少覆盖一次采样周期 */
uint32_t avg[8];                /* 8 个通道的平均值结果（由数据处理模块计算） */
uint32_t last_avg[8];  
volatile uint32_t flag = 0;     /* 数据处理标志位：1 表示 DMA 已完成、主循环需要进行处理 */

/* =========================
 * 按键回调函数
 * ========================= */
void on_key_b1_event(KeyEvent_t event)
{
    if (event == KEY_EVENT_SHORT_PRESS) {
        printf("KEY B1 Short Press\n");
        // 短按逻辑...
    } else if (event == KEY_EVENT_LONG_PRESS) {
        printf("KEY B1 Long Press\n");
        // 长按逻辑...
    }
}

void on_key_b2_event(KeyEvent_t event)
{
    if (event == KEY_EVENT_SHORT_PRESS) {
        printf("KEY B2 Short Press\n");
        /* 示例：短按保存 EEPROM */
        DL_GPIO_togglePins(LED_PB22_PORT, LED_PB22_PIN);
        for (uint16_t i = 0; i < 8; i++) {
            EEPROM_TypeB_write(i, avg[i]);
        }
    } else if (event == KEY_EVENT_LONG_PRESS) {
        printf("KEY B2 Long Press\n");
        /* 示例：长按执行其他操作 */
    }
}

/* =========================
 * 主函数：系统初始化与主循环
 * 流程：
 * 1) 初始化系统与驱动库；
 * 2) 配置 DMA 的源地址（ADC12 FIFO）与目标地址（gADCSamples 缓冲区）；
 * 3) 使能 DMA 通道与 ADC12 中断；
 * 4) 在主循环中轮询标志位，触发数据处理；
 * ========================= */
int main(void)
{
    SYSCFG_DL_init();  /* 设备库与系统配置初始化，具体内容由 SysConfig 生成 */

    /* 确保在配置 DMA 之前不触发采样与事件 */
    DL_TimerA_stopCounter(TIMER_0_INST);
    
    EEPROM_TypeB_init();
    
    for (uint16_t i = 0; i < 8; i++) {
        uint32_t v = EEPROM_TypeB_readDataItem(i);
        if (gEEPROMTypeBSearchFlag) {
            last_avg[i] = v;
        } else {
            last_avg[i] = 0;
        }
        printf("last_avg[%d] = %d\n", i, last_avg[i]);
    }
    //printf("**************************\n");
    /* 配置 DMA 源、目标与传输大小
     * 源地址：ADC12 FIFO 地址（由驱动库提供）
     * 目标地址：采样缓冲区首地址 gADCSamples[0]
     * 传输大小：由 SysConfig/驱动配置决定（此处由其他配置文件控制）
     */
    DL_DMA_setSrcAddr(DMA, DMA_CH0_CHAN_ID,
                      (uint32_t) DL_ADC12_getFIFOAddress(ADC12_0_INST));
    DL_DMA_setDestAddr(DMA, DMA_CH0_CHAN_ID, (uint32_t)&gADCSamples[0]);

    DL_DMA_enableChannel(DMA, DMA_CH0_CHAN_ID);

    /* 使能 ADC12 中断（用于接收 DMA 完成事件） */
    NVIC_EnableIRQ(ADC12_0_INST_INT_IRQN);
    
    /* 初始化按键模块并注册回调 */
    key_init();
    key_register_callback(KEY_ID_B1, on_key_b1_event);
    key_register_callback(KEY_ID_B2, on_key_b2_event);
    
    /* 完成 DMA/中断配置后再启动定时器触发采样 */
    DL_TimerA_startCounter(TIMER_0_INST);

    while (1) {
        /* 数据处理部分：当 DMA 完成后，中断会将 flag 置为 1
         * 主循环检测到标志位后，调用数据处理模块完成平均值计算并重启定时器
         */
        if (flag) {
            process_avg_and_restart_timer();
        }
        
        /* 旧的 key_scan 调用已移除，逻辑移至回调函数 */
    }
}

/* =========================
 * ADC12 中断服务程序
 * 说明：
 * - 当 DMA 完成一次数据搬运（ADC12_IIDX_DMA_DONE）：
 *   1) 先停止定时器（防止在处理期间继续触发）；
 *   2) 将标志位置 1，通知主循环进行数据处理；
 * - 如有其他中断事件，根据需要在 default 分支中扩展。
 * ========================= */
void ADC12_0_INST_IRQHandler(void)
{
    switch (DL_ADC12_getPendingInterrupt(ADC12_0_INST)) {
        case DL_ADC12_IIDX_DMA_DONE:
            DL_TimerA_stopCounter(TIMER_0_INST); /* 停止定时器，避免处理期间继续计时 */
            flag = 1;                             /* 设置处理标志，主循环将进行数据处理 */
            break;
        default:
            break;
    }
}

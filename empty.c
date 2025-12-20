
/* 设备配置与驱动头文件 */
#include "ti_msp_dl_config.h"   /* 设备驱动库配置与外设句柄 */
#include "LED.h"                /* 可选：LED 指示相关 */
#include "UART.h"               /* 可选：UART 打印与通信相关 */
#include "eeprom_emulation_type_b.h"

/* 标准库头文件 */
#include <stdint.h>             /* 标准整型定义 */
#include <stdio.h>              /* 标准输入输出，用于调试打印 */
#include <stdlib.h>             /* for abs */

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

/* Calibration and System State */
typedef enum {
    STATE_NORMAL = 0,
    STATE_CALIB_BLACK,
    STATE_CALIB_WHITE
} SystemState_t;

volatile SystemState_t system_state = STATE_NORMAL;
uint32_t black_val[8];
uint32_t white_val[8];
uint32_t black_threshold[8];
uint32_t white_threshold[8];

/* EEPROM IDs */
#define EEPROM_ID_BLACK_START 0
#define EEPROM_ID_WHITE_START 8

/* Helper Functions */
void load_parameters(void) {
    for (int i = 0; i < 8; i++) {
        /* Read Black Thresholds */
        uint32_t val = EEPROM_TypeB_readDataItem(EEPROM_ID_BLACK_START + i);
        if (gEEPROMTypeBSearchFlag) {
            black_threshold[i] = val;
        } else {
            black_threshold[i] = 0; // Default if not found
        }
        
        /* Read White Thresholds */
        val = EEPROM_TypeB_readDataItem(EEPROM_ID_WHITE_START + i);
        if (gEEPROMTypeBSearchFlag) {
            white_threshold[i] = val;
        } else {
            white_threshold[i] = 4095; // Default max if not found
        }
        printf("CH%d: BlackTh=%u, WhiteTh=%u\n", i, black_threshold[i], white_threshold[i]);
    }
}

void save_parameters(void) {
    for (int i = 0; i < 8; i++) {
        EEPROM_TypeB_write(EEPROM_ID_BLACK_START + i, black_threshold[i]);
        EEPROM_TypeB_write(EEPROM_ID_WHITE_START + i, white_threshold[i]);
    }
    printf("Parameters saved to EEPROM.\n");
}


/* =========================
 * 按键回调函数
 * ========================= */
/**
 * @brief 按键 B1 事件回调函数
 * @note  长按：进入“黑基准”标定状态
 *        短按：在标定流程中依次采集黑/白基准并计算阈值；正常模式下仅打印提示
 */
void on_key_b1_event(KeyEvent_t event)
{
    /*------------------ 长按处理 ------------------*/
    if (event == KEY_EVENT_LONG_PRESS) {
        printf("Enter Calibration Mode (Black)\n");   /* 提示用户进入标定模式 */
        system_state = STATE_CALIB_BLACK;             /* 切换到“黑基准”标定状态 */
    }
    /*------------------ 短按处理 ------------------*/
    else if (event == KEY_EVENT_SHORT_PRESS) {
        /* 当前处于“黑基准”标定状态：采集黑基准值并切换到“白基准”标定 */
        if (system_state == STATE_CALIB_BLACK) {
            printf("Collecting Black Reference...\n");
            for (int i = 0; i < 8; i++) {
                black_val[i] = avg[i];                /* 记录当前 8 通道平均值作为黑基准 */
                printf("Black[%d]=%u ", i, black_val[i]);
            }
            printf("\nSwitch to White Calibration\n");
            system_state = STATE_CALIB_WHITE;       /* 进入下一步：白基准标定 */
        }
        /* 当前处于“白基准”标定状态：采集白基准并计算阈值 */
        else if (system_state == STATE_CALIB_WHITE) {
            printf("Collecting White Reference...\n");
            for (int i = 0; i < 8; i++) {
                white_val[i] = avg[i];                /* 记录当前 8 通道平均值作为白基准 */

                /* 计算阈值冗余量：取黑白差值的 20%（差值/5） */
                uint32_t diff = (white_val[i] > black_val[i]) ?
                                (white_val[i] - black_val[i]) :
                                (black_val[i] - white_val[i]);
                uint32_t redundancy = diff / 2;     /* 冗余区间，防止抖动 */

                /* 最终阈值：白阈值 = 白基准 - redundancy；黑阈值 = 黑基准 + redundancy */
                white_threshold[i] = white_val[i] - redundancy;
                black_threshold[i] = black_val[i] + redundancy;

                /* 打印本通道标定信息，方便调试 */
                printf("CH%d: W=%u, B=%u, Red=%u, W_Th=%u, B_Th=%u\n",
                       i, white_val[i], black_val[i], redundancy,
                       white_threshold[i], black_threshold[i]);
            }

            save_parameters();                        /* 将新阈值写入 EEPROM 保存 */
            system_state = STATE_NORMAL;            /* 标定完成，返回正常运行状态 */
            printf("Calibration Done. Saved.\n");
        }
        /* 正常模式下短按：仅打印提示，无其他动作 */
        else {
            printf("KEY B1 Short Press (Normal Mode)\n");
        }
    }
}

void on_key_b2_event(KeyEvent_t event)
{
    if (event == KEY_EVENT_SHORT_PRESS) {
        printf("KEY B2 Short Press\n");
    } else if (event == KEY_EVENT_LONG_PRESS) {
        printf("KEY B2 Long Press\n");
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

    /* Load thresholds from EEPROM */
    /* 从 EEPROM 加载已保存的阈值参数 */
    load_parameters();
    
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
            /* Update LEDs based on state and values */
            LED_update((uint32_t)system_state, avg, white_threshold, black_threshold);
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

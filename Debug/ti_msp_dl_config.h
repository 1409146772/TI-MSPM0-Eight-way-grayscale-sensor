/*
 * Copyright (c) 2023, Texas Instruments Incorporated - http://www.ti.com
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

/*
 *  ============ ti_msp_dl_config.h =============
 *  Configured MSPM0 DriverLib module declarations
 *
 *  DO NOT EDIT - This file is generated for the MSPM0G350X
 *  by the SysConfig tool.
 */
#ifndef ti_msp_dl_config_h
#define ti_msp_dl_config_h

#define CONFIG_MSPM0G350X
#define CONFIG_MSPM0G3507

#if defined(__ti_version__) || defined(__TI_COMPILER_VERSION__)
#define SYSCONFIG_WEAK __attribute__((weak))
#elif defined(__IAR_SYSTEMS_ICC__)
#define SYSCONFIG_WEAK __weak
#elif defined(__GNUC__)
#define SYSCONFIG_WEAK __attribute__((weak))
#endif

#include <ti/devices/msp/msp.h>
#include <ti/driverlib/driverlib.h>
#include <ti/driverlib/m0p/dl_core.h>

#ifdef __cplusplus
extern "C" {
#endif

/*
 *  ======== SYSCFG_DL_init ========
 *  Perform all required MSP DL initialization
 *
 *  This function should be called once at a point before any use of
 *  MSP DL.
 */


/* clang-format off */

#define POWER_STARTUP_DELAY                                                (16)


#define CPUCLK_FREQ                                                     32000000



/* Defines for TIMER_0 */
#define TIMER_0_INST                                                     (TIMA0)
#define TIMER_0_INST_IRQHandler                                 TIMA0_IRQHandler
#define TIMER_0_INST_INT_IRQN                                   (TIMA0_INT_IRQn)
#define TIMER_0_INST_LOAD_VALUE                                         (63999U)
#define TIMER_0_INST_PUB_0_CH                                                (1)



/* Defines for UART_0 */
#define UART_0_INST                                                        UART0
#define UART_0_INST_FREQUENCY                                            4000000
#define UART_0_INST_IRQHandler                                  UART0_IRQHandler
#define UART_0_INST_INT_IRQN                                      UART0_INT_IRQn
#define GPIO_UART_0_RX_PORT                                                GPIOA
#define GPIO_UART_0_TX_PORT                                                GPIOA
#define GPIO_UART_0_RX_PIN                                        DL_GPIO_PIN_11
#define GPIO_UART_0_TX_PIN                                        DL_GPIO_PIN_10
#define GPIO_UART_0_IOMUX_RX                                     (IOMUX_PINCM22)
#define GPIO_UART_0_IOMUX_TX                                     (IOMUX_PINCM21)
#define GPIO_UART_0_IOMUX_RX_FUNC                      IOMUX_PINCM22_PF_UART0_RX
#define GPIO_UART_0_IOMUX_TX_FUNC                      IOMUX_PINCM21_PF_UART0_TX
#define UART_0_BAUD_RATE                                                  (9600)
#define UART_0_IBRD_4_MHZ_9600_BAUD                                         (26)
#define UART_0_FBRD_4_MHZ_9600_BAUD                                          (3)





/* Defines for ADC12_0 */
#define ADC12_0_INST                                                        ADC0
#define ADC12_0_INST_IRQHandler                                  ADC0_IRQHandler
#define ADC12_0_INST_INT_IRQN                                    (ADC0_INT_IRQn)
#define ADC12_0_ADCMEM_0                                      DL_ADC12_MEM_IDX_0
#define ADC12_0_ADCMEM_0_REF                     DL_ADC12_REFERENCE_VOLTAGE_VDDA
#define ADC12_0_ADCMEM_0_REF_VOLTAGE_V                                       3.3
#define ADC12_0_ADCMEM_1                                      DL_ADC12_MEM_IDX_1
#define ADC12_0_ADCMEM_1_REF                     DL_ADC12_REFERENCE_VOLTAGE_VDDA
#define ADC12_0_ADCMEM_1_REF_VOLTAGE_V                                       3.3
#define ADC12_0_ADCMEM_2                                      DL_ADC12_MEM_IDX_2
#define ADC12_0_ADCMEM_2_REF                     DL_ADC12_REFERENCE_VOLTAGE_VDDA
#define ADC12_0_ADCMEM_2_REF_VOLTAGE_V                                       3.3
#define ADC12_0_ADCMEM_3                                      DL_ADC12_MEM_IDX_3
#define ADC12_0_ADCMEM_3_REF                     DL_ADC12_REFERENCE_VOLTAGE_VDDA
#define ADC12_0_ADCMEM_3_REF_VOLTAGE_V                                       3.3
#define ADC12_0_ADCMEM_4                                      DL_ADC12_MEM_IDX_4
#define ADC12_0_ADCMEM_4_REF                     DL_ADC12_REFERENCE_VOLTAGE_VDDA
#define ADC12_0_ADCMEM_4_REF_VOLTAGE_V                                       3.3
#define ADC12_0_ADCMEM_5                                      DL_ADC12_MEM_IDX_5
#define ADC12_0_ADCMEM_5_REF                     DL_ADC12_REFERENCE_VOLTAGE_VDDA
#define ADC12_0_ADCMEM_5_REF_VOLTAGE_V                                       3.3
#define ADC12_0_ADCMEM_6                                      DL_ADC12_MEM_IDX_6
#define ADC12_0_ADCMEM_6_REF                     DL_ADC12_REFERENCE_VOLTAGE_VDDA
#define ADC12_0_ADCMEM_6_REF_VOLTAGE_V                                       3.3
#define ADC12_0_ADCMEM_7                                      DL_ADC12_MEM_IDX_7
#define ADC12_0_ADCMEM_7_REF                     DL_ADC12_REFERENCE_VOLTAGE_VDDA
#define ADC12_0_ADCMEM_7_REF_VOLTAGE_V                                       3.3
#define ADC12_0_INST_SUB_CH                                                  (1)
#define GPIO_ADC12_0_C0_PORT                                               GPIOA
#define GPIO_ADC12_0_C0_PIN                                       DL_GPIO_PIN_27
#define GPIO_ADC12_0_C1_PORT                                               GPIOA
#define GPIO_ADC12_0_C1_PIN                                       DL_GPIO_PIN_26
#define GPIO_ADC12_0_C2_PORT                                               GPIOA
#define GPIO_ADC12_0_C2_PIN                                       DL_GPIO_PIN_25
#define GPIO_ADC12_0_C3_PORT                                               GPIOA
#define GPIO_ADC12_0_C3_PIN                                       DL_GPIO_PIN_24
#define GPIO_ADC12_0_C5_PORT                                               GPIOB
#define GPIO_ADC12_0_C5_PIN                                       DL_GPIO_PIN_24
#define GPIO_ADC12_0_C6_PORT                                               GPIOB
#define GPIO_ADC12_0_C6_PIN                                       DL_GPIO_PIN_20
#define GPIO_ADC12_0_C7_PORT                                               GPIOA
#define GPIO_ADC12_0_C7_PIN                                       DL_GPIO_PIN_22



/* Defines for DMA_CH0 */
#define DMA_CH0_CHAN_ID                                                      (0)
#define ADC12_0_INST_DMA_TRIGGER                      (DMA_ADC0_EVT_GEN_BD_TRIG)


/* Defines for B2: GPIOA.8 with pinCMx 19 on package pin 54 */
#define KEY_B2_PORT                                                      (GPIOA)
#define KEY_B2_PIN                                               (DL_GPIO_PIN_8)
#define KEY_B2_IOMUX                                             (IOMUX_PINCM19)
/* Defines for B3: GPIOB.3 with pinCMx 16 on package pin 51 */
#define KEY_B3_PORT                                                      (GPIOB)
#define KEY_B3_PIN                                               (DL_GPIO_PIN_3)
#define KEY_B3_IOMUX                                             (IOMUX_PINCM16)
/* Defines for PB21: GPIOB.21 with pinCMx 49 on package pin 20 */
#define KEY_PB21_PORT                                                    (GPIOB)
#define KEY_PB21_PIN                                            (DL_GPIO_PIN_21)
#define KEY_PB21_IOMUX                                           (IOMUX_PINCM49)
/* Defines for LED0: GPIOB.6 with pinCMx 23 on package pin 58 */
#define LED_LED0_PORT                                                    (GPIOB)
#define LED_LED0_PIN                                             (DL_GPIO_PIN_6)
#define LED_LED0_IOMUX                                           (IOMUX_PINCM23)
/* Defines for LED1: GPIOA.7 with pinCMx 14 on package pin 49 */
#define LED_LED1_PORT                                                    (GPIOA)
#define LED_LED1_PIN                                             (DL_GPIO_PIN_7)
#define LED_LED1_IOMUX                                           (IOMUX_PINCM14)
/* Defines for LED2: GPIOA.6 with pinCMx 11 on package pin 46 */
#define LED_LED2_PORT                                                    (GPIOA)
#define LED_LED2_PIN                                             (DL_GPIO_PIN_6)
#define LED_LED2_IOMUX                                           (IOMUX_PINCM11)
/* Defines for LED3: GPIOA.9 with pinCMx 20 on package pin 55 */
#define LED_LED3_PORT                                                    (GPIOA)
#define LED_LED3_PIN                                             (DL_GPIO_PIN_9)
#define LED_LED3_IOMUX                                           (IOMUX_PINCM20)
/* Defines for LED4: GPIOA.16 with pinCMx 38 on package pin 9 */
#define LED_LED4_PORT                                                    (GPIOA)
#define LED_LED4_PIN                                            (DL_GPIO_PIN_16)
#define LED_LED4_IOMUX                                           (IOMUX_PINCM38)
/* Defines for LED5: GPIOA.15 with pinCMx 37 on package pin 8 */
#define LED_LED5_PORT                                                    (GPIOA)
#define LED_LED5_PIN                                            (DL_GPIO_PIN_15)
#define LED_LED5_IOMUX                                           (IOMUX_PINCM37)
/* Defines for LED6: GPIOA.13 with pinCMx 35 on package pin 6 */
#define LED_LED6_PORT                                                    (GPIOA)
#define LED_LED6_PIN                                            (DL_GPIO_PIN_13)
#define LED_LED6_IOMUX                                           (IOMUX_PINCM35)
/* Defines for LED7: GPIOA.12 with pinCMx 34 on package pin 5 */
#define LED_LED7_PORT                                                    (GPIOA)
#define LED_LED7_PIN                                            (DL_GPIO_PIN_12)
#define LED_LED7_IOMUX                                           (IOMUX_PINCM34)
/* Defines for PB22: GPIOB.22 with pinCMx 50 on package pin 21 */
#define LED_PB22_PORT                                                    (GPIOB)
#define LED_PB22_PIN                                            (DL_GPIO_PIN_22)
#define LED_PB22_IOMUX                                           (IOMUX_PINCM50)

/* clang-format on */

void SYSCFG_DL_init(void);
void SYSCFG_DL_initPower(void);
void SYSCFG_DL_GPIO_init(void);
void SYSCFG_DL_SYSCTL_init(void);
void SYSCFG_DL_TIMER_0_init(void);
void SYSCFG_DL_UART_0_init(void);
void SYSCFG_DL_ADC12_0_init(void);
void SYSCFG_DL_DMA_init(void);


bool SYSCFG_DL_saveConfiguration(void);
bool SYSCFG_DL_restoreConfiguration(void);

#ifdef __cplusplus
}
#endif

#endif /* ti_msp_dl_config_h */

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




/* Defines for B2: GPIOA.8 with pinCMx 19 on package pin 54 */
#define KEY_B2_PORT                                                      (GPIOA)
#define KEY_B2_PIN                                               (DL_GPIO_PIN_8)
#define KEY_B2_IOMUX                                             (IOMUX_PINCM19)
/* Defines for B3: GPIOB.3 with pinCMx 16 on package pin 51 */
#define KEY_B3_PORT                                                      (GPIOB)
#define KEY_B3_PIN                                               (DL_GPIO_PIN_3)
#define KEY_B3_IOMUX                                             (IOMUX_PINCM16)
/* Defines for LED0: GPIOB.6 with pinCMx 23 on package pin 58 */
#define LED_LED0_PORT                                                    (GPIOB)
#define LED_LED0_PIN                                             (DL_GPIO_PIN_6)
#define LED_LED0_IOMUX                                           (IOMUX_PINCM23)
/* Defines for LED1: GPIOA.11 with pinCMx 22 on package pin 57 */
#define LED_LED1_PORT                                                    (GPIOA)
#define LED_LED1_PIN                                            (DL_GPIO_PIN_11)
#define LED_LED1_IOMUX                                           (IOMUX_PINCM22)
/* Defines for LED2: GPIOA.10 with pinCMx 21 on package pin 56 */
#define LED_LED2_PORT                                                    (GPIOA)
#define LED_LED2_PIN                                            (DL_GPIO_PIN_10)
#define LED_LED2_IOMUX                                           (IOMUX_PINCM21)
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

/* clang-format on */

void SYSCFG_DL_init(void);
void SYSCFG_DL_initPower(void);
void SYSCFG_DL_GPIO_init(void);
void SYSCFG_DL_SYSCTL_init(void);



#ifdef __cplusplus
}
#endif

#endif /* ti_msp_dl_config_h */

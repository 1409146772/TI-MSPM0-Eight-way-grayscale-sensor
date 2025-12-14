#include "key.h"
#include "ti_msp_dl_config.h"
#include <ti/driverlib/driverlib.h>

void key_init(void)
{
}

static uint8_t keys_all_released(void)
{
    return DL_GPIO_readPins(KEY_B2_PORT, KEY_B2_PIN) &&
           DL_GPIO_readPins(KEY_B3_PORT, KEY_B3_PIN) &&
           DL_GPIO_readPins(KEY_PB21_PORT, KEY_PB21_PIN);
}

uint8_t key_scan(void)
{
    static uint8_t key_up = 1;
    uint8_t key = 0;
    if (key_up) {
        if (DL_GPIO_readPins(KEY_B2_PORT, KEY_B2_PIN) == 0) {
            key = 1;
        } else if (DL_GPIO_readPins(KEY_B3_PORT, KEY_B3_PIN) == 0) {
            key = 2;
        } else if (DL_GPIO_readPins(KEY_PB21_PORT, KEY_PB21_PIN) == 0) {
            key = 3;
        }
        if (key) {
            key_up = 0;
        }
    } else {
        if (keys_all_released()) {
            key_up = 1;
        }
    }
    return key;
}

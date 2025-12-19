I will implement the requested feature by utilizing the existing key interrupt and callback mechanism, and adding a helper function to control all LEDs simultaneously.

**1. Modify `LED.h` and `LED.c`**
*   Add a new function `void LED_Control_All(uint8_t state)` to `LED.c` and declare it in `LED.h`.
*   This function will iterate through the 8 LEDs and turn them all ON or OFF based on the `state` parameter.

**2. Modify `empty.c`**
*   Implement a key event callback function `key_callback(KeyEvent_t event)`.
    *   On `KEY_EVENT_SHORT_PRESS`: Call `LED_Control_All(1)` to turn ON all LEDs.
    *   On `KEY_EVENT_LONG_PRESS`: Call `LED_Control_All(0)` to turn OFF all LEDs.
*   In `main()`:
    *   Register this callback for Key 1 using `key_register_callback(KEY_ID_B1, key_callback)`.
    *   Comment out the undefined `key_scan()` logic in the main loop to prevent errors and conflicts.

This approach uses the non-blocking interrupt-driven key handling already present in the codebase, which is more efficient than the polling loop.
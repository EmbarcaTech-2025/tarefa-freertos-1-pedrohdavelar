#include "include/led_matrix.h"

void hal_led_init() {
    npInit(LED_PIN); // from original code
}

void hal_led_clear() {
    npClear();
}

void hal_led_write() {
    npWrite();
}

void hal_led_set_brightness(uint8_t brightness) {
    npSetBrightness(brightness);
}

void hal_set_led_red(int x, int y){
    npSetLED(getIndex(x, y), 255, 0, 0);
}

void hal_set_led_green(int x, int y){
    npSetLED(getIndex(x, y), 0, 255, 0);
}

void hal_set_led_blue(int x, int y){
    npSetLED(getIndex(x, y), 0, 0, 255);
}
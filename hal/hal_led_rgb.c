#include "include/led_rgb.h"

void hal_init_rgb_led() {
    init_rgb_led();
}

void hal_set_rgb_led(uint8_t r, uint8_t g, uint8_t b) {
    set_rgb_led(r, g, b);
}

void hal_set_rgb_color(rgb_colors_t color) {
    switch(color) {
        case COLOR_RED:     set_rgb_led RGB_RED; break;
        case COLOR_GREEN:   set_rgb_led RGB_GREEN; break;
        case COLOR_BLUE:    set_rgb_led RGB_BLUE; break;
        case COLOR_WHITE:   set_rgb_led RGB_WHITE; break;
        case COLOR_YELLOW:  set_rgb_led RGB_YELLOW; break;
        case COLOR_CYAN:    set_rgb_led RGB_CYAN; break;
        case COLOR_MAGENTA: set_rgb_led RGB_MAGENTA; break;
        case COLOR_ORANGE:  set_rgb_led RGB_ORANGE; break;
        case COLOR_PURPLE:  set_rgb_led RGB_PURPLE; break;
        case COLOR_PINK:    set_rgb_led RGB_PINK; break;
        case COLOR_OFF:     set_rgb_led RGB_OFF; break;
        default:            set_rgb_led RGB_OFF; break;
    }
}
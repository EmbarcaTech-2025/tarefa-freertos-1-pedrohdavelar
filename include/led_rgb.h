#ifndef LED_RGB_H
#define LED_RGB_H

#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/pwm.h"

#define LEDR 13
#define LEDG 11
#define LEDB 12

#define BRIGHTNESS_MAX 255
#define BRIGHTNESS_MID 128
#define BRIGHTNESS_MIN 0

typedef enum {
    COLOR_RED,
    COLOR_GREEN,
    COLOR_BLUE,
    COLOR_WHITE,
    COLOR_YELLOW,
    COLOR_CYAN,
    COLOR_MAGENTA,
    COLOR_ORANGE,
    COLOR_PURPLE,
    COLOR_PINK,
    COLOR_OFF
} rgb_colors_t;

// RGB color macros (format: R, G, B)
#define RGB_RED         (255, 0, 0)
#define RGB_GREEN       (0, 255, 0)
#define RGB_BLUE        (0, 0, 255)
#define RGB_WHITE       (255, 255, 255)
#define RGB_YELLOW      (255, 255, 0)
#define RGB_CYAN        (0, 255, 255)
#define RGB_MAGENTA     (255, 0, 255)
#define RGB_ORANGE      (255, 165, 0)
#define RGB_PURPLE      (128, 0, 128)
#define RGB_PINK        (255, 192, 203)
#define RGB_OFF         (0, 0, 0)

void init_rgb_led();
void hal_init_rgb_led();
void set_rgb_led(uint8_t r, uint8_t g, uint8_t b);
void hal_set_rgb_led(uint8_t r, uint8_t g, uint8_t b);
void hal_set_rgb_color(rgb_colors_t color);

#endif

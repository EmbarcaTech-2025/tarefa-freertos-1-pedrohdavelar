#ifndef LED_MATRIX_H
#define LED_MATRIX_H

#include "hardware/pio.h"
#include "hardware/gpio.h"
#include <stdint.h>

#define LED_COUNT 25
#define LED_PIN 7

typedef struct {
    uint8_t R, G, B;
} pixel_t;

typedef pixel_t npLED_t;

void npInit(uint pin);
void npSetLED(const uint index, uint8_t r, uint8_t g, uint8_t b);
void npClear();
void npWrite();
int getIndex(int x, int y);
void npSetFigure(npLED_t figure[5][5]);
void npSetBrightness(uint8_t brightness);

void hal_set_led_red(int x, int y);
void hal_set_led_green(int x, int y);
void hal_set_led_blue(int x, int y)

#endif
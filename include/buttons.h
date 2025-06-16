#ifndef BUTTONS_H
#define BUTTONS_H

#include <stdio.h>
#include <stdbool.h>
#include "pico/time.h"

#define A_BUTTON_PIN 5
#define B_BUTTON_PIN 6
#define J_BUTTON_PIN 22
#define DEBOUNCE_TIME_MS 175

typedef struct {
    uint8_t gpioPin;
    volatile int pressCount;
    volatile bool isPressed;
    absolute_time_t lastPressed;
} buttonState;

extern buttonState buttonA, buttonB, buttonJ;

void init_button(buttonState *button, uint8_t pin);
void hal_buttons_init();
bool hal_button_a_pressed();
bool hal_button_b_pressed();
bool hal_button_j_pressed();
bool hal_button_a_single_press();
bool hal_button_b_single_press();
bool hal_button_j_single_press();
void hal_wait_button_press();

#endif
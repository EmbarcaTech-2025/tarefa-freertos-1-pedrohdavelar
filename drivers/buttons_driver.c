#include "include/buttons.h"
#include "pico/time.h"
#include "hardware/gpio.h"

buttonState buttonA, buttonB, buttonJ;



void gpio_callback(uint gpio, uint32_t events) {
    buttonState* button;
    if (gpio == A_BUTTON_PIN) button = &buttonA;
    else if (gpio == B_BUTTON_PIN) button = &buttonB;
    else if (gpio == J_BUTTON_PIN) button = &buttonJ;
    else return;

    absolute_time_t now = get_absolute_time();
    int64_t elapsedTime = absolute_time_diff_us(button->lastPressed, now);

    if (elapsedTime >= DEBOUNCE_TIME_MS * 1000) {
        if (events & GPIO_IRQ_EDGE_FALL) {
            button->pressCount += 1;
            button->isPressed = true;
            button->lastPressed = now;
        }
        if (events & GPIO_IRQ_EDGE_RISE) {
            button->isPressed = false;
        }
    }
}

void init_button(buttonState *button, uint8_t pin) {
    button->gpioPin = pin;
    button->pressCount = 0;
    button->isPressed = false;
    button->lastPressed = get_absolute_time();

    gpio_init(pin);
    gpio_set_dir(pin, GPIO_IN);
    gpio_pull_up(pin);
    gpio_set_irq_enabled_with_callback(pin, GPIO_IRQ_EDGE_RISE | GPIO_IRQ_EDGE_FALL, true, &gpio_callback);
}
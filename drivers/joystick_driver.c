#include "include/joystick.h"
#include "hardware/adc.h"
#include "pico/time.h"

joystickState joystick;

#define JOYSTICK_X_PIN 26
#define JOYSTICK_Y_PIN 27
#define JOYSTICK_MIN -100
#define JOYSTICK_MAX 100
#define DEADZONE 20
#define THRESHOLD 75
#define DEBOUNCE_TIME_MS_JOYSTICK 200

void initJoystick() {
    adc_init();
    adc_gpio_init(JOYSTICK_X_PIN);
    adc_gpio_init(JOYSTICK_Y_PIN);
    joystick.lastUpdate = get_absolute_time();
}

int mapJoystickValue(uint16_t adcValue) {
    return (adcValue * (JOYSTICK_MAX - JOYSTICK_MIN) / 4095) + JOYSTICK_MIN;
}

int readJoystick() {
    adc_select_input(1);
    uint adcX = adc_read();
    joystick.x = mapJoystickValue(adcX);
    sleep_us(2);
    adc_select_input(0);
    uint adcY = adc_read();
    joystick.y = mapJoystickValue(adcY);
    sleep_us(2);

    if (abs(joystick.x) < DEADZONE) joystick.x = 0;
    if (abs(joystick.y) < DEADZONE) joystick.y = 0;

    absolute_time_t now = get_absolute_time();
    int64_t elapsedTime = absolute_time_diff_us(joystick.lastUpdate, now);

    if (elapsedTime >= DEBOUNCE_TIME_MS_JOYSTICK * 1000 && !joystick.directionChanged) {
        if (joystick.x > THRESHOLD) {
            joystick.directionChanged = true;
            joystick.lastUpdate = now;
            return joyRIGHT;
        } else if (joystick.x < -THRESHOLD) {
            joystick.directionChanged = true;
            joystick.lastUpdate = now;
            return joyLEFT;
        } else if (joystick.y > THRESHOLD) {
            joystick.directionChanged = true;
            joystick.lastUpdate = now;
            return joyUP;
        } else if (joystick.y < -THRESHOLD) {
            joystick.directionChanged = true;
            joystick.lastUpdate = now;
            return joyDOWN;
        } else {
            return joyCENTER;
        }
    }
    joystick.directionChanged = false;
    return joyCENTER;
}
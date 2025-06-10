#include "include/joystick.h"

void hal_joystick_init() {
    initJoystick();
}

int hal_joystick_read_direction() {
    return readJoystick();
}
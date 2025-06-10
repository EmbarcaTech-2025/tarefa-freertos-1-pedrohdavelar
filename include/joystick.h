#ifndef JOYSTICK_H
#define JOYSTICK_H

#include <stdlib.h>
#include "pico/time.h"

#define joyCENTER 0
#define joyUP 1
#define joyDOWN 2
#define joyLEFT 3
#define joyRIGHT 4

typedef struct {
    int x;
    int y;
    int direction;
    bool directionChanged;
    absolute_time_t lastUpdate;
} joystickState;

extern joystickState joystick;

void initJoystick();
int readJoystick();
int hal_joystick_read_direction();

#endif
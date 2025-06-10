#ifndef BUZZER_H
#define BUZZER_H

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include "pico/types.h"
#include "pico/stdlib.h"
#include "hardware/pwm.h"
#include "hardware/pwm.h"
#include "hardware/clocks.h"
#include "pico/time.h"
#include "include/led_rgb.h"

#define BUZZER_PIN_1 21
#define BUZZER_PIN_2 10
#define SAMPLING_RATE 8000 // Taxa de amostragem do PWM
#define PWM_FREQUENCY 200000   // Frequência do PWM
#define GAIN_RATE 2.2f // Fator de ganho aplicado ao sinal PWM

void pwm_init_buzzer();
void play_sample(uint16_t frequency);
void play_tone (uint16_t * data, size_t size);
void play_beep(uint16_t frequency, uint duration_ms);
void hal_buzzer_init();
void hal_play_tone(uint16_t * data, size_t size);
void hal_beep();
void hal_beep_frequency(uint frequency, uint duration_ms);
void hal_countdown_beep();
void hal_shutdown_beep();

#endif // BUZZER_H
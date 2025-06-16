#include "include/buzzer.h"

void hal_buzzer_init() {
    pwm_init_buzzer();
}
void hal_beep(int gpio_pin, int duration_ms) {
    beep(gpio_pin, duration_ms);
}

void hal_double_beep(int duration_ms) {
    double_beep(duration_ms);
}

void hal_play_note(int gpio_pin, int frequency, int duration_ms) {
    play_note(gpio_pin, frequency, duration_ms);
}

void hal_play_notes(int frequency1, int frequency2, int duration_ms) {
    play_notes(frequency1, frequency2, duration_ms);
}

void hal_play_melody(int gpio_pin, const Note melody[], int length) {
    play_melody(gpio_pin, melody, length);
}

void hal_play_harmony_melody(const HarmonyNote melody[], int length){
    play_harmony_melody(melody, length);
}
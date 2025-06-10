#include "include/buzzer.h"

void hal_buzzer_init() {
    pwm_init_buzzer();
}

void hal_play_tone(uint16_t * data, size_t size) {
    hal_set_rgb_color(COLOR_GREEN); // Define a cor do LED RGB para verde
    play_tone(data, size);
    hal_set_rgb_color(COLOR_OFF);
}

void hal_beep() {
    play_beep(1000, 100); // Beep padrão de 1000 Hz por 100 ms
}

void hal_beep_frequency(uint frequency, uint duration_ms) {
    play_beep(frequency, duration_ms); // Beep com frequência e duração especificadas
}

void hal_countdown_beep() {
    for (int i = 11; i > 1; --i) {
        play_beep(i * 100, 500); // Beep de contagem regressiva de 11 a 2
        sleep_ms(500); // Pausa de 500 ms entre os beeps
    }
}

void hal_shutdown_beep() {
    for (int i = 0; i < 3; ++i) {
        play_beep(1000, 200); // Beep de desligamento de 1000 Hz por 200 ms
        sleep_ms(300); // Pausa de 300 ms entre os beeps
    }
}
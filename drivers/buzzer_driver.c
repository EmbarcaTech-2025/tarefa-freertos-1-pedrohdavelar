#include "include/buzzer.h"




void pwm_init_buzzer() {
    gpio_set_function(BUZZER_A_PIN, GPIO_FUNC_PWM);
    gpio_set_function(BUZZER_B_PIN, GPIO_FUNC_PWM);
    uint slice_a = pwm_gpio_to_slice_num(BUZZER_A_PIN);
    uint slice_b = pwm_gpio_to_slice_num(BUZZER_B_PIN);
    pwm_set_enabled(slice_a, true);
    pwm_set_enabled(slice_b, true);
}

void set_buzzer_frequency(int gpio_pin, uint32_t freq) {
    uint slice_num = pwm_gpio_to_slice_num(gpio_pin);

    if (freq == 0) {
        // A frequency of 0 means silence, so we set the duty cycle to 0.
        pwm_set_gpio_level(gpio_pin, 0);
        return;
    }
    
    // The system clock is typically 125,000,000 Hz
    uint32_t clock = clock_get_hz(clk_sys);
    
    // Formula to calculate the divider to get max resolution (wrap value)
    uint32_t divider16 = clock / freq / 4096 + (clock % (freq * 4096)!= 0);
    if (divider16 / 16 == 0) {
        divider16 = 16;
    }

    // Calculate the wrap value for the given frequency and divider
    uint32_t wrap = clock * 16 / divider16 / freq - 1;

    pwm_set_clkdiv_int_frac(slice_num, divider16 / 16, divider16 & 0xF);
    pwm_set_wrap(slice_num, wrap);

    // Set duty cycle to 50% for a standard square wave tone
    pwm_set_gpio_level(gpio_pin, wrap / 2);
}

// --- Monophonic (Single Buzzer) Mode ---

// Plays a simple beep at a fixed frequency
void beep(uint gpio_pin, int duration_ms) {
    set_buzzer_frequency(gpio_pin, 1000); // 1kHz beep
    busy_wait_ms(duration_ms);
    pwm_set_gpio_level(gpio_pin, 0);
}

void double_beep(int duration_ms) {
    set_buzzer_frequency(BUZZER_A_PIN, 1000); // 1kHz beep
    set_buzzer_frequency(BUZZER_B_PIN, 1500); // 1.5kHz beep
    busy_wait_ms(duration_ms);
    pwm_set_gpio_level(BUZZER_A_PIN, 0);
    pwm_set_gpio_level(BUZZER_B_PIN, 0);
}

// Plays a single note for a given duration on one buzzer
void play_note(int gpio_pin, int frequency, int duration_ms) {
    set_buzzer_frequency(gpio_pin, frequency);
    busy_wait_ms(duration_ms);
    pwm_set_gpio_level(gpio_pin, 0); // Silence buzzer after note
}

void play_notes(int frequency1, int frequency2, int duration_ms) {
    set_buzzer_frequency(BUZZER_A_PIN, frequency1);
    set_buzzer_frequency(BUZZER_B_PIN, frequency2);
    busy_wait_ms(duration_ms);
    pwm_set_gpio_level(BUZZER_A_PIN, 0); // Silence buzzer A
    pwm_set_gpio_level(BUZZER_B_PIN, 0); // Silence buzzer B
}

// Plays a melody from an array of Note structs on one buzzer
void play_melody(int gpio_pin,const Note melody[], int length) {
    for (int i = 0; i < length; i++) {
        play_note(gpio_pin, melody[i].frequency, melody[i].duration_ms);
        // A small pause between notes can make them more distinct
        busy_wait_ms(20);
    }
}

// --- Polyphonic (Dual Buzzer) Mode ---

// Plays a harmony melody from an array of HarmonyNote structs
void play_harmony_melody(const HarmonyNote melody[], int length) {
    for (int i = 0; i < length; i++) {
        // Set frequencies for both buzzers simultaneously
        set_buzzer_frequency(BUZZER_A_PIN, melody[i].frequency1);
        set_buzzer_frequency(BUZZER_B_PIN, melody[i].frequency2);

        // Wait for the shared duration
        busy_wait_ms(melody[i].duration_ms);
    }
    // Silence both buzzers at the end of the melody
    pwm_set_gpio_level(BUZZER_A_PIN, 0);
    pwm_set_gpio_level(BUZZER_B_PIN, 0);
}
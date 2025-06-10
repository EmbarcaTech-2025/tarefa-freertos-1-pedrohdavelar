#include "include/buzzer.h"




void pwm_init_buzzer() {
    gpio_set_function(BUZZER_PIN_1, GPIO_FUNC_PWM);
    gpio_set_function(BUZZER_PIN_2, GPIO_FUNC_PWM);
    
    uint sliceNum1 = pwm_gpio_to_slice_num(BUZZER_PIN_1);
    uint sliceNum2 = pwm_gpio_to_slice_num(BUZZER_PIN_2);

    pwm_config config = pwm_get_default_config();
    
    uint32_t wrap = clock_get_hz(clk_sys) / PWM_FREQUENCY;
    pwm_config_set_wrap(&config, wrap);
    
    pwm_config_set_clkdiv(&config, 1.0f);
    pwm_init(sliceNum1, &config, true);
    pwm_init(sliceNum2, &config, true);
}



// Play a single sample (modified version)
void play_sample(uint16_t sample_value) {
    uint32_t boostedSample = (uint32_t)(sample_value * GAIN_RATE);
    if (boostedSample > 4095) {
        boostedSample = 4095; // Clamp to max 12-bit value
    }
    
    // Convert 12-bit ADC sample to PWM duty cycle
    uint slice_num = pwm_gpio_to_slice_num(BUZZER_PIN_1);
    uint32_t pwm_top = pwm_hw->slice[slice_num].top;
    uint32_t level = (boostedSample * (pwm_top + 1)) / 4095; 
    
    pwm_set_gpio_level(BUZZER_PIN_1, level);
    pwm_set_gpio_level(BUZZER_PIN_2, level);
    
    // Wait for exactly one sample period (125µs for 8kHz)
    busy_wait_us(1000000/SAMPLING_RATE);
}

// Play a complete tone (optimized)
void play_tone(uint16_t *data, size_t size) {
    printf("Playing tone with %zu samples...\n", size);
    absolute_time_t start_time = get_absolute_time();
    
    for(size_t i = 0; i < size; i++) {
        play_sample(data[i]);
    }
    
    int64_t duration_us = absolute_time_diff_us(start_time, get_absolute_time());
    printf("Tone completed in %.2f ms\n", duration_us/1000.0f);
}

void play_beep(uint16_t frequency, uint duration_ms) {
    // Calculate how many samples we need for the requested duration
    size_t num_samples = (SAMPLING_RATE * duration_ms) / 1000;
    
    // Create a buffer for the generated tone
    uint16_t *tone_buffer = (uint16_t *)malloc(num_samples * sizeof(uint16_t));
    if (!tone_buffer) {
        printf("Error allocating tone buffer!\n");
        return;
    }
    
    // Fill buffer with the requested frequency
    for (size_t i = 0; i < num_samples; ++i) {
        // For a pure tone, we could generate a sine wave here
        // But for a simple buzzer, we'll just use the frequency directly
        tone_buffer[i] = frequency;
    }
    
    // Play the generated tone
    printf("Playing %dHz beep for %dms...\n", frequency, duration_ms);
    play_tone(tone_buffer, num_samples);
    
    // Clean up
    free(tone_buffer);
}
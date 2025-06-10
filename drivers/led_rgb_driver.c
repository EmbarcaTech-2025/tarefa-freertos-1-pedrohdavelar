#include "include/led_rgb.h"

uint slice_r, slice_g, slice_b;
uint16_t pwm_r = 0, pwm_g = 0, pwm_b = 0;

void init_rgb_led(){
    gpio_set_function(LEDR, GPIO_FUNC_PWM);
    gpio_set_function(LEDG, GPIO_FUNC_PWM);
    gpio_set_function(LEDB, GPIO_FUNC_PWM);
    slice_r = pwm_gpio_to_slice_num(LEDR);
    slice_g = pwm_gpio_to_slice_num(LEDG);
    slice_b = pwm_gpio_to_slice_num(LEDB);
    pwm_config config = pwm_get_default_config();
    pwm_config_set_clkdiv(&config, 4.f);
    pwm_config_set_wrap(&config, 255);
    pwm_init(slice_r, &config, true);
    pwm_init(slice_g, &config, true);
    pwm_init(slice_b, &config, true);
    pwm_set_gpio_level(LEDR, pwm_r);
    pwm_set_gpio_level(LEDG, pwm_g);
    pwm_set_gpio_level(LEDB, pwm_b);
}



void set_rgb_led(uint8_t r, uint8_t g, uint8_t b) {
    pwm_r = r;
    pwm_g = g;
    pwm_b = b;
    pwm_set_gpio_level(LEDR, pwm_r);
    pwm_set_gpio_level(LEDG, pwm_g);
    pwm_set_gpio_level(LEDB, pwm_b);
}
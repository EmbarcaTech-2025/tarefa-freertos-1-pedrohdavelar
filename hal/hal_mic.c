#include "include/mic.h"

void hal_mic_init() {
    init_mic();
}

void hal_mic_sample() {
    hal_set_rgb_color(COLOR_RED); // Define a cor do LED RGB para vermelho
    sample_mic();
    hal_set_rgb_color(COLOR_OFF);
//    smooth_mic_samples();
    dynamic_range_compression();
    print_mic_samples();
}


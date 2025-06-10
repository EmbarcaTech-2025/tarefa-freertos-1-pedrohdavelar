#ifndef MIC_H
#define MIC_H

#include <stdio.h>
#include <math.h>
#include "pico/stdlib.h"
#include "hardware/adc.h"
#include "hardware/dma.h"
#include "include/led_rgb.h"

// Definições do microfone.
// O microfone é conectado ao ADC do Raspberry Pi Pico, usando o canal 2.
#define MIC_CHANNEL 2
#define MIC_PIN (26 + MIC_CHANNEL)

// Parâmetros e macros do ADC.
#define ADC_CLOCK_DIV 96.f
#define ADC_SAMPLE_RATE 8000 // Taxa de amostragem do ADC.
#define ADC_DURATION_S 8 // Duração da amostragem em segundos.
#define ADC_BUFFER_SIZE (ADC_SAMPLE_RATE * ADC_DURATION_S) // Tamanho do buffer de amostras.
#define ADC_ADJUST(x) (x * 3.3f / (1 << 12u) - 1.65f) // Ajuste do valor do ADC para Volts.
#define ADC_MAX 3.3f
#define ADC_STEP (3.3f/5.f) // Intervalos de volume do microfone.
#define ADC_SMOOTHING_FACTOR 0.2f // Fator de suavização para o filtro passa-baixa.
#define ADC_GAIN 2.2f // Ganho aplicado à saída do ADC.
#define ADC_DYNAMIC_COMPRESSION 0.7f // Fator de compressão dinâmica aplicado ao sinal do microfone.

extern uint16_t adc_buffer[ADC_BUFFER_SIZE] __attribute__((aligned(4)));

void init_mic();
void sample_mic();
float mic_power();
uint8_t get_intensity(float v);
void smooth_mic_samples();
void dynamic_range_compression();
void print_mic_samples();
void hal_mic_init();
void hal_mic_sample();
void hal_smooth_mic_samples();
void hal_print_mic_samples();
#endif // MIC_H
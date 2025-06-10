#include "include/mic.h"

// Canal e configurações do DMA
uint dma_channel;
dma_channel_config dma_cfg;

// Buffer de amostras do ADC.
uint16_t adc_buffer[ADC_BUFFER_SIZE] __attribute__((aligned(4)));

void init_mic(){
    adc_init();
    adc_gpio_init(MIC_PIN);
    adc_select_input(MIC_CHANNEL);
    adc_fifo_setup(
    true, // Habilitar FIFO
    true, // Habilitar request de dados do DMA
    1, // Threshold para ativar request DMA é 1 leitura do ADC
    false, // Não usar bit de erro
    false // Não fazer downscale das amostras para 8-bits, manter 12-bits.
    );
    adc_set_clkdiv(48000000/ADC_SAMPLE_RATE);
    dma_channel = dma_claim_unused_channel(true);

    // Configurações do DMA.
    dma_cfg = dma_channel_get_default_config(dma_channel);
    channel_config_set_transfer_data_size(&dma_cfg, DMA_SIZE_16); // Tamanho da transferência é 16-bits (usamos uint16_t para armazenar valores do ADC)
    channel_config_set_read_increment(&dma_cfg, false); // Desabilita incremento do ponteiro de leitura (lemos de um único registrador)
    channel_config_set_write_increment(&dma_cfg, true); // Habilita incremento do ponteiro de escrita (escrevemos em um array/buffer)
    channel_config_set_dreq(&dma_cfg, DREQ_ADC); // Usamos a requisição de dados do ADC
}


/**
 * Realiza as leituras do ADC e armazena os valores no buffer.
 */
void sample_mic() {
  printf("Iniciando amostragem do microfone...\n");
  adc_fifo_drain(); // Limpa o FIFO do ADC.
  adc_run(false); // Desliga o ADC (se estiver ligado) para configurar o DMA.

  dma_channel_configure(dma_channel, &dma_cfg,
    adc_buffer, // Escreve no buffer.
    &(adc_hw->fifo), // Lê do ADC.
    ADC_BUFFER_SIZE, // Faz "SAMPLES" amostras.
    true // Liga o DMA.
  );

  // Liga o ADC e espera acabar a leitura.
  adc_run(true);
  dma_channel_wait_for_finish_blocking(dma_channel);
  
  // Acabou a leitura, desliga o ADC de novo.
  adc_run(false);
  printf("Amostragem do microfone concluída.\n");
}

/**
 * Calcula a potência média das leituras do ADC. (Valor RMS)
 */
float mic_power() {
  float avg = 0.f;

  for (uint i = 0; i < ADC_BUFFER_SIZE; ++i)
    avg += adc_buffer[i] * adc_buffer[i];
  
  avg /= ADC_BUFFER_SIZE;
  return sqrt(avg);
}

/**
 * Calcula a intensidade do volume registrado no microfone, de 0 a 4, usando a tensão.
 */
uint8_t get_intensity(float v) {
  uint count = 0;

  while ((v -= ADC_STEP/20) > 0.f)
    ++count;
  
  return count;
}


void smooth_mic_samples() {
    // Suaviza as amostras do microfone usando um filtro passa-baixa.
    float last_sample = adc_buffer[0];
    for (uint i = 1; i < ADC_BUFFER_SIZE; ++i) {
        adc_buffer[i] = (ADC_SMOOTHING_FACTOR * adc_buffer[i]) + ((1 - ADC_SMOOTHING_FACTOR) * last_sample);
        last_sample = adc_buffer[i];
    }
}

void dynamic_range_compression(){
  float threshold = ADC_DYNAMIC_COMPRESSION;
  for (int i = 0; i < ADC_BUFFER_SIZE; ++i){
    float sample = adc_buffer[i]/4095.0f;
    if(sample > threshold) {
            sample = threshold + (sample-threshold)/2.0f; // Soft clipping
    }
    adc_buffer[i] = sample * 4095.0f;
  }
}



void print_mic_samples() {
    // Imprime as amostras do microfone no console.
    for (uint i = 0; i < ADC_BUFFER_SIZE; ++i) {
        printf("%d ", adc_buffer[i]);
        if ((i + 1) % 16 == 0) {
            printf("\n");
        }
    }
    printf("\n");
}
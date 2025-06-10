#include "include/hal_ssd1306.h"
#include "hardware/i2c.h"
#include <string.h>

#define I2C_SDA_PIN 14
#define I2C_SCL_PIN 15

uint8_t ssd[ssd1306_buffer_length];

struct render_area frame_area = {
    start_column : 0,
    end_column : ssd1306_width - 1,
    start_page : 0,
    end_page : ssd1306_n_pages - 1
};

//Inicialização do display OLED SSD1306 com comunicação I2C.
void hal_ssd1306_init(void){
    i2c_init(i2c1, ssd1306_i2c_clock * 1000);
    gpio_set_function(I2C_SDA_PIN, GPIO_FUNC_I2C);
    gpio_set_function(I2C_SCL_PIN, GPIO_FUNC_I2C);
    gpio_pull_up(I2C_SDA_PIN);
    gpio_pull_up(I2C_SCL_PIN);
    ssd1306_init();
    calculate_render_area_buffer_length(&frame_area);
}

//limpa o buffer de memória do display OLED SSD1306.
void hal_ssd1306_clear(void){
    memset(ssd, 0, ssd1306_buffer_length);
}

//renderiza o buffer de memória do display OLED SSD1306.
void hal_ssd1306_render(void){
    render_on_display(ssd, &frame_area);
}

//desenha ou um pixel no buffer de memória do display OLED SSD1306.
void hal_ssd1306_draw_pixel(int x, int y, bool set){
    ssd1306_set_pixel(ssd, x, y, set);
}

//desenha uma string no buffer de memória do display OLED SSD1306.
//o display tem resolução de 128x64; para caracteres de 8x8 da um total de
//16x8 caracteres
void hal_ssd1306_draw_string(int x, int y, char *string){
    ssd1306_draw_string(ssd, x * 8, y * 8, string);
}

//desenha um inteiro
void hal_ssd1306_draw_int(int x, int y, int value){
    char buffer[16];
    snprintf(buffer, sizeof(buffer), "%d", value);
    hal_ssd1306_draw_string(x, y, buffer);
}

//desenha um digito
void hal_ssd1306_draw_digit(int x, int y, int value){
    char buffer[1];
    if (value >= 10){
        value = 9;
    } else if (value < 0){
        value = 0;
    }
    snprintf(buffer, sizeof(buffer), "%d", value);
    hal_ssd1306_draw_string(x, y, buffer);
}

//desenha uma linha para cima, para imprimir a gaussiana do galton board
void hal_ssd1306_draw_up_line(int x_pos, int qt){
    for(int i = 0; i < qt; i++){
        hal_ssd1306_draw_pixel(x_pos, 54 - i, true);
    }
}

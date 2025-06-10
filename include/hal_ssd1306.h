#ifndef HAL_SSD1306_H
#define HAL_SSD1306_H

#include "include/ssd1306.h"
#include <stdio.h>

//Inicialização do display OLED SSD1306 com comunicação I2C.
void hal_ssd1306_init(void);

//limpa o buffer de memória do display OLED SSD1306.
void hal_ssd1306_clear(void);

//renderiza o buffer de memória do display OLED SSD1306.
void hal_ssd1306_render(void);

//desenha ou um pixel no buffer de memória do display OLED SSD1306.
void hal_ssd1306_draw_pixel(int x, int y, bool set);

//desenha uma string no buffer de memória do display OLED SSD1306.
//o display tem resolução de 128x64; para caracteres de 8x8 da um total de
//16x8 caracteres
void hal_ssd1306_draw_string(int x, int y, char *string);

void hal_ssd1306_draw_int(int x, int y, int value);

void hal_ssd1306_draw_digit(int x, int y, int value);

void hal_ssd1306_draw_up_line(int x_pos, int qt);

#endif // HAL_SSD1306_H
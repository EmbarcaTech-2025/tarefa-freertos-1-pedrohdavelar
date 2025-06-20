//Bibliotecas FreeRTOS
#include "FreeRTOS.h"
#include "task.h"
#include "semphr.h" 

#include <stdio.h>

//Bibliotecas padrão do Pico SDK
#include "pico/stdlib.h" // Biblioteca padrão pico
#include "hardware/gpio.h" // Biblioteca de GPIOs
#include "hardware/adc.h" // Biblioteca do ADC
#include "hardware/pwm.h" // Biblioteca do PWM
#include "hardware/i2c.h" // Biblioteca do I2C

//Bibliotecas HAL
#include "buttons.h"
#include "joystick.h"
#include "buzzer.h"
#include "include/hal_ssd1306.h"
#include "led_rgb.h"

//Handles das tarefas
TaskHandle_t led_task_handle = NULL;
TaskHandle_t buzzer_task_handle = NULL;

//Semaforos das tarefas
SemaphoreHandle_t xLedSemaphore;    
SemaphoreHandle_t xBuzzerSemaphore; 

//situação daas tarefas
bool led_task_running = true;
bool buzzer_task_running = true;

enum {
  LED_RED,
  LED_GREEN,
  LED_BLUE,
} ledStatus;

enum {
  BUZZER_OFF,
  BUZZER_ON,
} buzzerStatus;

void display_task(){
  while(true){
    hal_ssd1306_clear();
    switch(ledStatus) {
      case LED_RED:
        hal_ssd1306_draw_string(0, 0, "LED: RED");
        break;
      case LED_GREEN:
        hal_ssd1306_draw_string(0, 0, "LED: GREEN");
        break;
      case LED_BLUE:
        hal_ssd1306_draw_string(0, 0, "LED: BLUE");
        break;
    }
    if (led_task_running) {
      hal_ssd1306_draw_string(0, 1, "LED Task: ON");
    } else {
      hal_ssd1306_draw_string(0, 1, "LED Task: OFF");
    }
    switch(buzzerStatus) {
      case BUZZER_OFF:
        hal_ssd1306_draw_string(0, 2, "Buzzer: OFF");
        break;
      case BUZZER_ON:
        hal_ssd1306_draw_string(0, 2, "Buzzer: ON");
        break;
    }
    if (buzzer_task_running) {
      hal_ssd1306_draw_string(0, 3, "Buzzer Task: ON");
    } else {
      hal_ssd1306_draw_string(0, 3, "Buzzer Task: OFF");
    }
    hal_ssd1306_render();
    vTaskDelay(10);
  }
}

void led_task() {
  while (true) {
    if(xSemaphoreTake(xLedSemaphore, portMAX_DELAY) == pdTRUE){
      switch (ledStatus){
        case LED_RED:
          hal_set_rgb_color(COLOR_GREEN);
          ledStatus = LED_GREEN;
          break;
        case LED_GREEN:
          hal_set_rgb_color(COLOR_BLUE);
          ledStatus = LED_BLUE;
          break;
        case LED_BLUE:
          hal_set_rgb_color(COLOR_RED);
          ledStatus = LED_RED;
          break;
      }
      xSemaphoreGive(xLedSemaphore);
    }
    vTaskDelay(1000);
  }
}

void buzzer_task(){
  while (true){
    if (xSemaphoreTake(xBuzzerSemaphore, portMAX_DELAY) == pdTRUE){
      buzzerStatus = BUZZER_ON;
      hal_double_beep(250);
      buzzerStatus = BUZZER_OFF;
      xSemaphoreGive(xBuzzerSemaphore);
    }
    vTaskDelay(2000); // Aguarda 2 segundos antes de tocar novamente
  }
}

void button_task(){
  while (true){
    if (hal_button_a_single_press()){
      //Tarefa estava parada, ativando
      if (uxSemaphoreGetCount(xLedSemaphore) == 0){
        led_task_running = true;
        xSemaphoreGive(xLedSemaphore);
      //Tarefa estava ativa, suspendendo
      } else {
        led_task_running = false;
        xSemaphoreTake(xLedSemaphore, 0);
      }
    } 
    if (hal_button_b_single_press()){
      if (uxSemaphoreGetCount(xBuzzerSemaphore) == 0){
        buzzer_task_running = true;
        xSemaphoreGive(xBuzzerSemaphore);
      } else {
        buzzer_task_running = false;
        xSemaphoreTake(xBuzzerSemaphore, 0);
      }
    }
    vTaskDelay(10); 
  }
}


int main() {
   stdio_init_all();
   hal_ssd1306_init(); // Inicializa o display OLED SSD1306 com comunicação I2C.
   hal_buzzer_init(); // Inicializa o buzzer.
   hal_buttons_init(); // Inicializa os botões.
   hal_init_rgb_led(); // Inicializa o LED RGB.
    
  hal_ssd1306_clear();
  hal_ssd1306_draw_string(0, 0, "BitDogLab RTOS  ");
  hal_ssd1306_draw_string(0, 1, "Free RTOS Demo  ");
  hal_ssd1306_draw_string(0, 2, "by pedrohdavelar");
  hal_ssd1306_draw_string(0, 5, "Pressione       ");      
  hal_ssd1306_draw_string(0, 6, "  qualquer botao");
  hal_ssd1306_draw_string(0, 7, "para iniciar!   ");
  hal_ssd1306_render();
  hal_wait_button_press();

  xLedSemaphore = xSemaphoreCreateBinary();
  xBuzzerSemaphore = xSemaphoreCreateBinary();
  xSemaphoreGive(xLedSemaphore);
  xSemaphoreGive(xBuzzerSemaphore);

  xTaskCreate(led_task, "LED_Task", 256, NULL, 1, &led_task_handle);
  xTaskCreate(buzzer_task, "Buzzer_Task", 256, NULL, 1, &buzzer_task_handle);
  xTaskCreate(button_task, "Button_Task", 256, NULL, 1, NULL);
  xTaskCreate(display_task, "Display_Task", 256, NULL, 2, NULL);
  vTaskStartScheduler();

  while(1){
        
  };
}
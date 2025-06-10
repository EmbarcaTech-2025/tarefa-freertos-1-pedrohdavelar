#include "include/buttons.h"

void hal_buttons_init() {
    init_button(&buttonA, A_BUTTON_PIN);
    init_button(&buttonB, B_BUTTON_PIN);
    init_button(&buttonJ, J_BUTTON_PIN);
}

bool hal_button_a_pressed() {
    return buttonA.isPressed;
}

bool hal_button_b_pressed() {
    return buttonB.isPressed;
}

bool hal_button_j_pressed() {
    return buttonJ.isPressed;
}

bool hal_button_a_single_press(){
    if (buttonA.isPressed){
        buttonA.isPressed = false;
        printf("Button A single press!\n");
        return true;
    }
    return false;
}

bool hal_button_b_single_press(){
    if (buttonB.isPressed){
        buttonB.isPressed = false;
        printf("Button B single press!\n");
        return true;
    }
    return false;
}

bool hal_button_j_single_press(){
    if (buttonJ.isPressed){
        buttonJ.isPressed = false;
        printf("Button J single press!\n");
        return true;
    }
    return false;
}

void hal_wait_button_press(){
    while(!hal_button_a_single_press() && !hal_button_b_single_press() && !hal_button_j_single_press()){
        // Aguarda o botão A, B ou J serem pressionados
    }
}
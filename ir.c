#include "ir.h"


void Buzzer_init(){
    GPIO_InitPortPin(BUZZER_PORT_CR, BUZZER_PIN, GPIO_OUT);
}

void IR_init(){
    GPIO_InitPortPin(IR1_PORT_CR, IR1_PIN, GPIO_IN);
    GPIO_InitPortPin(IR1_PORT_CR, IR1_PIN, GPIO_IN);
}

void Buzzer_toggle(){
    GPIO_WritePortPin(BUZZER_PORT_DR, BUZZER_PIN, 1);
}
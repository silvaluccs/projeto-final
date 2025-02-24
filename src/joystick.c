#include "pico/stdlib.h"
#include "hardware/adc.h"
#include "joystick.h"

void controle_joystick(Posicao *posicao) {

    adc_select_input(1);
    uint16_t valor_eixo_x = adc_read();
   
    adc_select_input(0);
    uint16_t valor_eixo_y = adc_read();

    posicao->x = valor_eixo_x;
    posicao->y = valor_eixo_y;

}
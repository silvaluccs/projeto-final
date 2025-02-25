#include "pico/stdlib.h"
#include "leds.h"
#include "joystick.h"
#include "controle_menu.h"

void gerenciar_leds(uint pino_led_vermelho, uint pino_led_azul, uint pino_led_verde, Posicao posicao_joystick, DADOS_SISTEMA dados_sistema) {
 

    if (dados_sistema.modo_operacao == MANUAL) {

        if (posicao_joystick.y > 3500 ) {
            alarme_reservatorio_cheio(pino_led_vermelho, pino_led_azul, pino_led_verde);
          }
          else if (posicao_joystick.y < 1000 ) {
            alarme_reservatorio_vazio(pino_led_vermelho, pino_led_azul, pino_led_verde);
          } 
          else {
              alarme_reservatorio_nivel_medio(pino_led_vermelho, pino_led_azul, pino_led_verde);
          }      

    }

   
}

void alarme_reservatorio_vazio(uint pino_led_vermelho, uint pino_led_azul, uint pino_led_verde) {
    gpio_put(pino_led_vermelho, 0);
    gpio_put(pino_led_azul, 0);
    gpio_put(pino_led_verde, 1);
}


void alarme_reservatorio_cheio(uint pino_led_vermelho, uint pino_led_azul, uint pino_led_verde) {
    gpio_put(pino_led_vermelho, 1);
    gpio_put(pino_led_azul, 0);
    gpio_put(pino_led_verde, 0);
}


void alarme_reservatorio_nivel_medio(uint pino_led_vermelho, uint pino_led_azul, uint pino_led_verde) {
    gpio_put(pino_led_vermelho, 1);
    gpio_put(pino_led_azul, 0);
    gpio_put(pino_led_verde, 1);
}
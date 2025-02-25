#ifndef LEDS_H
#define LEDS_H

#include "pico/stdlib.h"
#include "joystick.h"
#include "controle_menu.h"

void gerenciar_leds(uint pino_led_vermelho, uint pino_led_azul, uint pino_led_verde, Posicao posicao_joystick, DADOS_SISTEMA dados_sistema);
void alarme_reservatorio_vazio(uint pino_led_vermelho, uint pino_led_azul, uint pino_led_verde);
void alarme_reservatorio_cheio(uint pino_led_vermelho, uint pino_led_azul, uint pino_led_verde);
void alarme_reservatorio_nivel_medio(uint pino_led_vermelho, uint pino_led_azul, uint pino_led_verde);

#endif
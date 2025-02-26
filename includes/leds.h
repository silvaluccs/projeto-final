#ifndef LEDS_H
#define LEDS_H

#include "pico/stdlib.h"
#include "joystick.h"
#include "controle_menu.h"

void gerenciar_leds(uint pino_led_vermelho, uint pino_led_azul, uint pino_led_verde, Posicao posicao_joystick, DADOS_SISTEMA dados_sistema);
void alarme_reservatorio_vazio(uint pino_led_vermelho, uint pino_led_azul, uint pino_led_verde);
void alarme_reservatorio_cheio(uint pino_led_vermelho, uint pino_led_azul, uint pino_led_verde);
void alarme_reservatorio_nivel_medio(uint pino_led_vermelho, uint pino_led_azul, uint pino_led_verde);
static inline void colocar_pixel(uint32_t pixel_rgb);
static inline uint32_t urgb_u32(uint8_t r, uint8_t g, uint8_t b);
void desenhar(uint8_t r, uint8_t g, uint8_t b, bool *frame_numero_atual);
void gerenciar_matriz_leds(uint pino_matriz_leds, int nivel_reservatorio);

#endif
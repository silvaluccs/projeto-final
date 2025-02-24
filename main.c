#include <stdlib.h>
#include "pico/stdlib.h"
#include "ssd1306.h"
#include "setup.h"
#include "controle_menu.h"
#include "joystick.h"
#include <stdio.h>

const uint pino_botao_a = 5;
const uint pino_botao_b = 6;
const uint pino_vrx = 27; // pino do eixo X do joystick
const uint pino_vry = 26; // pino do eixo Y do joystick
const uint pino_botao_joystick = 22; // pino do botão do joystick

void gpio_irq_handler(uint gpio, uint32_t events); // prototipo da função para tratar a interrupção dos botoes

bool repeating_timer_callback_menu(struct repeating_timer *t); // prototipo da função para o timer

bool repeating_timer_callback_joystick(struct repeating_timer *t); // prototipo da função para o timer


Posicao posicao_joystick; // estrutura para armazenar a posição do joystick

ssd1306_t ssd;


int main()
{
  stdio_init_all();

  setup_botoes(pino_botao_a);
  setup_botoes(pino_botao_b);

  setup_joystick(pino_vrx, pino_vry, pino_botao_joystick); // configuração do joystick

  setup_display();
  init_display(&ssd);

  // timer para verificar se tem entradda
  struct repeating_timer timer_menu;
  add_repeating_timer_ms(100, repeating_timer_callback_menu, NULL, &timer_menu);
  
  struct repeating_timer timer_joystick;
  add_repeating_timer_ms(100, repeating_timer_callback_joystick, NULL, &timer_joystick);

  // definindo uma interrupção para os botoes na borda de descida
  gpio_set_irq_enabled_with_callback(pino_botao_a, GPIO_IRQ_EDGE_FALL, true, &gpio_irq_handler); // botao A
  bool repeating_timer_callback(struct repeating_timer *t); // prototipo da função para o timer

  // Limpa o display. O display inicia com todos os pixels apagados.
  ssd1306_fill(&ssd, false);
  ssd1306_send_data(&ssd);
  

  while (true)
  {
    tight_loop_contents();
 
  }
}


void gpio_irq_handler(uint gpio, uint32_t events) {
// TODO
}


bool repeating_timer_callback_menu(struct repeating_timer *t) {


  menu_principal(&ssd, &posicao_joystick);
  return true;

}


bool repeating_timer_callback_joystick(struct repeating_timer *t) {
  controle_joystick(&posicao_joystick);
  printf("X: %d Y: %d\n", posicao_joystick.x, posicao_joystick.y);
  return true;
}
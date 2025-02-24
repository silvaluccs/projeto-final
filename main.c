#include <stdlib.h>
#include "pico/stdlib.h"
#include "ssd1306.h"
#include "setup.h"
#include "controle_menu.h"

const uint pino_botao_a = 5;
const uint pino_botao_b = 6;

void gpio_irq_handler(uint gpio, uint32_t events); // prototipo da função para tratar a interrupção dos botoes
bool repeating_timer_callback(struct repeating_timer *t); // prototipo da função para o timer


ssd1306_t ssd;

int main()
{
  stdio_init_all();

  setup_botoes(pino_botao_a);
  setup_botoes(pino_botao_b);

  

  setup_display();
  init_display(&ssd);

  // timer para verificar se tem entradda
  struct repeating_timer timer;
  add_repeating_timer_ms(100, repeating_timer_callback, NULL, &timer);
  
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


bool repeating_timer_callback(struct repeating_timer *t) {

  menu_principal(&ssd);
  return true;

}
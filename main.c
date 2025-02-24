#include <stdlib.h>
#include "pico/stdlib.h"
#include "ssd1306.h"
#include "setup.h"


const uint pino_botao_a = 5;
const uint pino_botao_b = 6;

void gpio_irq_handler(uint gpio, uint32_t events); // prototipo da função para tratar a interrupção dos botoes


int main()
{
  stdio_init_all();

  setup_botoes(pino_botao_a);
  setup_botoes(pino_botao_b);

  ssd1306_t ssd;

  setup_display();
  init_display(&ssd);

  // Limpa o display. O display inicia com todos os pixels apagados.
  ssd1306_fill(&ssd, false);
  ssd1306_send_data(&ssd);

    // definindo uma interrupção para os botoes na borda de descida
  gpio_set_irq_enabled_with_callback(pino_botao_a, GPIO_IRQ_EDGE_FALL, true, &gpio_irq_handler); // botao A
 

  while (true)
  {
    tight_loop_contents();
 
  }
}


void gpio_irq_handler(uint gpio, uint32_t events) {

}
#include <stdlib.h>
#include "pico/stdlib.h"
#include "ssd1306.h"
#include "setup.h"
#include "controle_menu.h"
#include "joystick.h"
#include <stdio.h>
#include "debouce.h"
#include "leds.h"


const uint pino_botao_a = 5; // variável para armazenar o pino do botão A
const uint pino_botao_b = 6;
const uint pino_vrx = 27; // pino do eixo X do joystick
const uint pino_vry = 26; // pino do eixo Y do joystick
const uint pino_botao_joystick = 22; // pino do botão do joystick
const uint pino_led_vermelho = 13; // pino do led vermelho
const uint pino_led_azul = 12; // pino do led amarelo
const uint pino_led_verde = 11; // pino do led verde
const uint pino_matriz_leds = 7; // pino da matriz de leds

void gpio_irq_handler(uint gpio, uint32_t events); // prototipo da função para tratar a interrupção dos botoes

bool repeating_timer_callback_menu(struct repeating_timer *t); // prototipo da função para o timer

bool repeating_timer_callback_joystick(struct repeating_timer *t); // prototipo da função para o timer

bool repeating_timer_callback_nivel_matriz(struct repeating_timer *t);

static uint32_t ultimo_tempo = 0; // variável para armazenar o último tempo de acionamento do botão

bool entrar_menu = false; // variável para controlar a entrada no menu
Posicao posicao_joystick; // estrutura para armazenar a posição do joystick
DADOS_SISTEMA dados_sistema; // estrutura para armazenar os dados do sistema

ssd1306_t ssd;


int main()
{
  stdio_init_all();

  setup_botoes(pino_botao_a);
  setup_botoes(pino_botao_b); // configuração dos botões

  setup_joystick(pino_vrx, pino_vry, pino_botao_joystick); // configuração do joystick
  setup_matriz_leds(pino_matriz_leds);  // inicializando a matriz de leds

  setup_display(); // inicializando o display
  init_display(&ssd);

  setup_led(pino_led_vermelho); // configuração dos leds
  setup_led(pino_led_azul);
  setup_led(pino_led_verde);

  dados_sistema.nivel_reservatorio = 100; // inicializando o nível do reservatório
  dados_sistema.modo_operacao = AUTOMATICO; /// inicializando o modo de operação
  dados_sistema.controle_bomba = PARAR; // inicializando o controle da bomba


  // timer para verificar se tem entradda
  struct repeating_timer timer_menu;
  add_repeating_timer_ms(100, repeating_timer_callback_menu, NULL, &timer_menu);
  
  // timer para verificar a posição do joystick
  struct repeating_timer timer_joystick;
  add_repeating_timer_ms(100, repeating_timer_callback_joystick, NULL, &timer_joystick);

  // timer para verificar o nível do reservatório
  struct repeating_timer timer_nivel_matriz;
  add_repeating_timer_ms(100, repeating_timer_callback_nivel_matriz, NULL, &timer_nivel_matriz);

  // definindo uma interrupção para os botoes na borda de descida
  gpio_set_irq_enabled_with_callback(pino_botao_a, GPIO_IRQ_EDGE_FALL, true, &gpio_irq_handler); // botao A
 
  // Limpa o display. O display inicia com todos os pixels apagados.
  ssd1306_fill(&ssd, false);
  ssd1306_send_data(&ssd);
  
  

  while (true) // loop infinito
  {
    tight_loop_contents(); // otimização do loop
 
  }
}


/*
* Função para tratar a interrupção dos botões
*/
void gpio_irq_handler(uint gpio, uint32_t events) { // função para tratar a interrupção dos botões

  if (!debouce(&ultimo_tempo)) { // verifica se o botão foi acionado recentemente
    return;
  }

  if (gpio == pino_botao_a) { // verifica se o botão A foi acionado
    entrar_menu = true;
    
  } 

}

/*
* Função para gerenciar o menu do display
*/
bool repeating_timer_callback_menu(struct repeating_timer *t) {


  gerenciar_menus(&ssd, &posicao_joystick, entrar_menu, &dados_sistema); // gerencia o menu
  entrar_menu = false; // reseta a variável de entrada no menu

  return true;

}

/*
* Função para gerenciar a posição do joystick
*/
bool repeating_timer_callback_joystick(struct repeating_timer *t) {
  controle_joystick(&posicao_joystick); // verifica a posição do joystick

 // exibe a posição do joystick no display 
  gerenciar_leds(pino_led_vermelho, pino_led_azul, pino_led_verde, posicao_joystick, dados_sistema);

  return true;
}


/*
* Função para gerenciar o nível do reservatório
*/
bool repeating_timer_callback_nivel_matriz(struct repeating_timer *t) {

  if (dados_sistema.modo_operacao == MANUAL) { // verifica se o modo de operação é manual
    uint porcetagem = (posicao_joystick.y * 100) / 4095; // calcula a porcentagem do nível do reservatório

    dados_sistema.nivel_reservatorio = porcetagem >= 97 ? 100 : porcetagem; // atualiza o nível do reservatório

  } else {

    if (dados_sistema.controle_bomba == ESVASIAR && dados_sistema.nivel_reservatorio > 0) {
      dados_sistema.nivel_reservatorio -= 1; // decrementa o nível do reservatório
    } else if (dados_sistema.controle_bomba == ENCHER && dados_sistema.nivel_reservatorio < 100) {
      dados_sistema.nivel_reservatorio += 1; // incrementa o nível do reservatório 
    } else {
      dados_sistema.nivel_reservatorio = dados_sistema.nivel_reservatorio; // mantém o nível do reservatório
    }

  }

  // exibe o nível do reservatório na matriz de leds
  gerenciar_matriz_leds(pino_matriz_leds, dados_sistema.nivel_reservatorio);

  return true;
}
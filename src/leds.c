#include "pico/stdlib.h"
#include "leds.h"
#include "joystick.h"
#include "controle_menu.h"
#include "hardware/pio.h"
#include "ws2812.pio.h"

const uint numero_pixels = 25;

static bool buffer_nivel_zero[25] = {
    0, 0, 0, 0, 0,
    0, 0, 0, 0, 0,
    0, 0, 0, 0, 0,
    0, 0, 0, 0, 0,
    0, 0, 0, 0, 0,
};


static bool buffer_nivel_um[25] = {
    0, 0, 0, 0, 0,
    0, 0, 0, 0, 0,
    0, 0, 0, 0, 0,
    0, 0, 0, 0, 0,
    1, 1, 1, 1, 1,
};

static bool buffer_nivel_dois[25] = {
    0, 0, 0, 0, 0,
    0, 0, 0, 0, 0,
    0, 0, 0, 0, 0,
    1, 1, 1, 1, 1,
    1, 1, 1, 1, 1,
};

static bool buffer_nivel_tres[25] = {
    0, 0, 0, 0, 0,
    0, 0, 0, 0, 0
    1, 1, 1, 1, 1,
    1, 1, 1, 1, 1,
    1, 1, 1, 1, 1,
};

static bool buffer_nivel_quatro[25] = {
    0, 0, 0, 0, 0,
    1, 1, 1, 1, 1,
    1, 1, 1, 1, 1,
    1, 1, 1, 1, 1,
    1, 1, 1, 1, 1,
};

static bool buffer_nivel_cinco[25] = {
    1, 1, 1, 1, 1,
    1, 1, 1, 1, 1,
    1, 1, 1, 1, 1,
    1, 1, 1, 1, 1,
    1, 1, 1, 1, 1,
};


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



void gerenciar_matriz_leds(uint pino_matriz_leds, int nivel_reservatorio) {
  
    int quantidade_linhas = nivel_reservatorio / 20;

    for (int i = 0; i < quantidade_linhas; i++) {
        
    

}


/*
* Função para enviar o pixel para a matriz de leds
*/
static inline void colocar_pixel(uint32_t pixel_rgb) {
    pio_sm_put_blocking(pio0, 0, pixel_rgb << 8u);
}


/*
* Função para converter os valores rgb
*/
static inline uint32_t urgb_u32(uint8_t r, uint8_t g, uint8_t b)
{
    return ((uint32_t)(r) << 8) | ((uint32_t)(g) << 16) | (uint32_t)(b);
}


void desenhar(uint8_t r, uint8_t g, uint8_t b, bool *frame_numero_atual)
{


    // Define a cor com base nos parâmetros fornecidos
    uint32_t cor = urgb_u32(r, g, b);

    // Define todos os LEDs com a cor especificada
    for (int i = 0; i < numero_pixels; i++)
    {
        if (frame_numero_atual[i])
        {
            colocar_pixel(cor); // Liga o LED com um no buffer
        }
        else
        {
            colocar_pixel(0);  // Desliga os LEDs com zero no buffer
        }
    }
}
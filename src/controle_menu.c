#include "pico/stdlib.h"
#include "ssd1306.h"
#include "menus.h"
#include "joystick.h"
#include "controle_menu.h"
#include "debouce.h"
#include <stdio.h>

const uint pin_botao_a = 5;
const uint pin_botao_b = 6;

MENU_PRINCIPAL menu_atual = NIVEL_RESERVATORIO;

static uint32_t ultimo_temp = 0;

void controle_bomba(ssd1306_t *ssd, DADOS_SISTEMA *dados)  {

    while (true) {

        if (gpio_get(pin_botao_b) == 0) {
            
            if (!debouce(&ultimo_temp)) {
                continue;
            }
            break;
        }

        ssd1306_fill(ssd, false);

        if (dados->controle_bomba == ESVASIAR) {
            ssd1306_draw_string(ssd, "ESVASIAR", 20, 30);
        } else if (dados->controle_bomba == ENCHER) {
            ssd1306_draw_string(ssd, "ENCHER", 20, 30);
        } else {
            ssd1306_draw_string(ssd, "PARAR", 20, 30);
        }

        ssd1306_send_data(ssd);

        if (gpio_get(pin_botao_a) == 0) {
            
            if (!debouce(&ultimo_temp)) {
                continue;
            }

            switch (dados->controle_bomba) {
                case ESVASIAR:
                    dados->controle_bomba = ENCHER;
                    break;
                case ENCHER:
                    dados->controle_bomba = PARAR;
                    break;
                case PARAR:
                    dados->controle_bomba = ESVASIAR;
                    break;

            }
        }
    }
}


void nivel_reservatorio(ssd1306_t *ssd, uint nivel) {

    char str[10];  // Buffer suficiente

    
    
    while (gpio_get(pin_botao_b) != 0) {
        sprintf(str, "%up", nivel);  // Adiciona '%' no final
        ssd1306_fill(ssd, false);
        ssd1306_draw_string(ssd, str, 40, 30);
        ssd1306_send_data(ssd);    
    }
 
}

void modo_operacao(ssd1306_t *ssd, DADOS_SISTEMA *dados) {
    
    while (true) {

        if (gpio_get(pin_botao_b) == 0) {
            
            if (!debouce(&ultimo_temp)) {
                continue;
            }
            break;
        }

        ssd1306_fill(ssd, false);
        
        if (dados->modo_operacao == MANUAL) {
            ssd1306_draw_string(ssd, "MANUAL", 20, 30);
        } else {
            ssd1306_draw_string(ssd, "AUTOMATICO", 20, 30);
        }

        ssd1306_send_data(ssd);    

        if (gpio_get(pin_botao_a) == 0) {

            if (!debouce(&ultimo_temp)) {
                continue;
            }

            dados->modo_operacao = (dados->modo_operacao == MANUAL) ? AUTOMATICO : MANUAL;
        }

        
    }   
        
 
}

void menu_principal(ssd1306_t *ssd, Posicao *posicao) {

    if (posicao->x < 600 && menu_atual > 0) {
        menu_atual--;
    } else if (posicao->x > 3500 && menu_atual < 3) {
        menu_atual++;
    }

    ssd1306_fill(ssd, false);

    switch (menu_atual) {
        case NIVEL_RESERVATORIO:
            ssd1306_draw_string(ssd, "PORCENTAGEM", 20, 30);
            ssd1306_draw_string(ssd, "AGUA", 20, 40);
            break;
        case MODO_OPERACAO:
            ssd1306_draw_string(ssd, "MODO", 20, 30);
            ssd1306_draw_string(ssd, "OPERACAO", 20, 40);
            break;
        case CONTROLE_BOMBA:
            ssd1306_draw_string(ssd, "CONTROLE", 20, 30);
            ssd1306_draw_string(ssd, "BOMBA", 20, 40);
            //    controle_bomba(ssd);
            break;
        
    }

    ssd1306_send_data(ssd); // Atualiza o display
}




void gerenciar_menus(ssd1306_t *ssd, Posicao *posicao, bool entrar_menu, DADOS_SISTEMA *dados)
{

    menu_principal(ssd, posicao);

    if (entrar_menu) {
        switch (menu_atual) {
            case NIVEL_RESERVATORIO:
                nivel_reservatorio(ssd, dados->nivel_reservatorio);
                break;
            case MODO_OPERACAO:
                modo_operacao(ssd, dados);
                break;
            case CONTROLE_BOMBA:
                if (dados->modo_operacao == AUTOMATICO) {
                    controle_bomba(ssd, dados);
                }
                break;
        }
    }


}

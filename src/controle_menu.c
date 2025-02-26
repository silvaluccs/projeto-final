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


/*
* Função para controlar a bomba de água
*/
void controle_bomba(ssd1306_t *ssd, DADOS_SISTEMA *dados)  {

    while (true) {

        if (gpio_get(pin_botao_b) == 0) { // Verifica se o botão B foi pressionado
            
            if (!debouce(&ultimo_temp)) {
                continue;
            }
            break;
        }

        ssd1306_fill(ssd, false);

        if (dados->controle_bomba == ESVASIAR) { // Verifica o estado da bomba 
            ssd1306_draw_string(ssd, "ESVASIAR", 20, 30);
        } else if (dados->controle_bomba == ENCHER) { // Verifica o estado da bomba
            ssd1306_draw_string(ssd, "ENCHER", 20, 30);
        } else {
            ssd1306_draw_string(ssd, "PARAR", 20, 30);
        }

        ssd1306_send_data(ssd);

        if (gpio_get(pin_botao_a) == 0) { // Verifica se o botão A foi pressionado
            
            if (!debouce(&ultimo_temp)) {
                continue;
            }

            switch (dados->controle_bomba) { // Altera o estado da bomba
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


/*
* Função para controlar o nível do reservatório
*/
void nivel_reservatorio(ssd1306_t *ssd, uint nivel) {

    char str[10];  // Buffer suficiente

    
    
    while (gpio_get(pin_botao_b) != 0) {  // Enquanto o botão B não for pressionado
        sprintf(str, "%up", nivel);  // Adiciona '%' no final
        ssd1306_fill(ssd, false);
        ssd1306_draw_string(ssd, str, 40, 30);
        ssd1306_send_data(ssd);    
    }
 
}

/*
* Função para controlar o modo de operação
*/
void modo_operacao(ssd1306_t *ssd, DADOS_SISTEMA *dados) {
    
    while (true) {

        if (gpio_get(pin_botao_b) == 0) { // Verifica se o botão B foi pressionado
            
            if (!debouce(&ultimo_temp)) {
                continue;
            }
            break;
        }

        ssd1306_fill(ssd, false);
        
        if (dados->modo_operacao == MANUAL) { // Verifica o modo de operação
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


/*
* Função para controlar o menu principal 
*/
void menu_principal(ssd1306_t *ssd, Posicao *posicao, MODOS_OPERACAO modo_op) {

    if (posicao->x < 600 && menu_atual > 0) { // move para a esquerda
        menu_atual--;
    } else if (posicao->x > 3500 && menu_atual < 2) { // move para a direita
        menu_atual++;
    }

    if (menu_atual == 2 && modo_op == MANUAL) { // Se o modo de operação for manual, não exibe o controle da bomba
        menu_atual--;
    }

    ssd1306_fill(ssd, false);

    switch (menu_atual) {
        case NIVEL_RESERVATORIO: // Exibe o menu de nível do reservatório
            ssd1306_draw_string(ssd, "PORCENTAGEM", 20, 30);
            ssd1306_draw_string(ssd, "RESERVATORIO", 20, 40);
            break;
        case MODO_OPERACAO: // Exibe o menu de modo de operação
            ssd1306_draw_string(ssd, "MODO", 20, 30);
            ssd1306_draw_string(ssd, "OPERACAO", 20, 40);
            break;
        case CONTROLE_BOMBA: // Exibe o menu de controle da bomba
            ssd1306_draw_string(ssd, "CONTROLE", 20, 30);
            ssd1306_draw_string(ssd, "BOMBA", 20, 40);
            //    controle_bomba(ssd);
            break;
        
    }

    ssd1306_send_data(ssd); // Atualiza o display
}



/*
* Função para gerenciar os menus
*/
void gerenciar_menus(ssd1306_t *ssd, Posicao *posicao, bool entrar_menu, DADOS_SISTEMA *dados)
{

    menu_principal(ssd, posicao, dados->modo_operacao); // Exibe o menu principal

    if (entrar_menu) { // Se o botão A for pressionado, exibe o menu selecionado
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

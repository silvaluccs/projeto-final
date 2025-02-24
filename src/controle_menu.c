#include "pico/stdlib.h"
#include "ssd1306.h"
#include "menus.h"
#include "joystick.h"
#include "controle_menu.h"
#include "debouce.h"

const uint pin_botao_a = 5;
const uint pin_botao_b = 6;

static volatile MENU_PRINCIPAL menu_atual = NIVEL_RESERVATORIO;

static uint32_t ultimo_temp = 0;

void nivel_reservatorio(ssd1306_t *ssd) {
    
    while (gpio_get(pin_botao_b) != 0) {
        ssd1306_fill(ssd, false);
        ssd1306_draw_string(ssd, "100p", 20, 30);
        ssd1306_send_data(ssd);    
    }
 
}

void modo_operacao(ssd1306_t *ssd, DADOS_SISTEMA *dados) {
    
    do {
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

        if (gpio_get(pin_botao_b) == 0) {
            
            if (!debouce(&ultimo_temp)) {
                continue;
            }
            break;
        }
    }   while (true);
        
 
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
        case CONFIGURACOES:
            ssd1306_draw_string(ssd, "CONFIGURACOES", 15, 30);
            break;
    }

    ssd1306_send_data(ssd); // Atualiza o display
}




void gerenciar_menus(ssd1306_t *ssd, Posicao *posicao, bool entrar_menu, DADOS_SISTEMA *dados) {

    menu_principal(ssd, posicao);

    if (entrar_menu) {
        switch (menu_atual) {
            case NIVEL_RESERVATORIO:
                nivel_reservatorio(ssd);
                break;
            case MODO_OPERACAO:
                modo_operacao(ssd, dados);
                break;
            case CONTROLE_BOMBA:
                break;
            case CONFIGURACOES:
                break;
        }
    }


}

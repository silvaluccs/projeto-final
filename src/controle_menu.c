#include "pico/stdlib.h"
#include "ssd1306.h"
#include "menus.h"
#include "joystick.h"

const uint pin_botao_a = 5;

static volatile MENU_PRINCIPAL menu_atual = MODO_OPERACAO;

void menu_principal(ssd1306_t *ssd, Posicao *posicao, bool entrar_menu) {

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
            nivel_reservatorio(ssd);
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



void nivel_reservatorio(ssd1306_t *ssd) {
    while (gpio_get(pin_botao_a) != 0) {
        ssd1306_fill(ssd, false);
        ssd1306_draw_string(ssd, "NIVEL RESERVATORIO", 10, 30);
        ssd1306_send_data(ssd);

    }
}

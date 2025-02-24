#include "pico/stdlib.h"
#include "ssd1306.h"
#include "menus.h"


static volatile MENU_PRINCIPAL menu_atual = CONFIGURACOES;


void menu_principal(ssd1306_t *ssd) {
    ssd1306_fill(ssd, false);

    switch (menu_atual) {
        case NIVEL_RESERVATORIO:
            ssd1306_draw_string(ssd, "PORCENTAGEM", 20, 30);
            ssd1306_draw_string(ssd, "AGUA", 20, 40);
            //    nivel_reservatorio(ssd);
            break;
        case MODO_OPERACAO:
            ssd1306_draw_string(ssd, "MODO", 20, 30);
            ssd1306_draw_string(ssd, "OPERACAO", 20, 40);
            //    modo_operacao(ssd);
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
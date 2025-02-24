#include "pico/stdlib.h"
#include "ssd1306.h"
#include "menus.h"


static volatile MENU_PRINCIPAL menu_atual = NIVEL_RESERVATORIO;


void menu_principal(ssd1306_t *ssd) {
    ssd1306_fill(ssd, false);

    switch (menu_atual) {
        case NIVEL_RESERVATORIO:
        ssd1306_draw_string(ssd, "Nivel Reservatorio", 20, 30);
        //    nivel_reservatorio(ssd);
            break;
        case MODO_OPERACAO:
        //    modo_operacao(ssd);
            break;
        case CONTROLE_BOMBA:
        //   controle_bomba(ssd);
            break;
        case ALERTAS_CONFIGURACAO:
        //    alertas_configuracao(ssd);
            break;
    }
    ssd1306_send_data(ssd); // Atualiza o display
}
#ifndef CONTROLE_MENU_H
#define CONTROLE_MENU_H

#include "pico/stdlib.h"
#include "ssd1306.h"
#include "joystick.h"

typedef enum  Controle_bomb {
    ESVASIAR,
    ENCHER,
    PARAR
} controle_bomba_t;

typedef enum MODOS_OPERACAO {
    MANUAL = 0,
    AUTOMATICO = 1
} MODOS_OPERACAO;


typedef struct dados_sistema {
    int nivel_reservatorio;
    MODOS_OPERACAO modo_operacao;
    controle_bomba_t controle_bomba;
} DADOS_SISTEMA;


void menu_principal(ssd1306_t *ssd, Posicao *posicao);
void nivel_reservatorio(ssd1306_t *ssd, uint nivel);
void modo_operacao(ssd1306_t *ssd, DADOS_SISTEMA *dados);
void gerenciar_menus(ssd1306_t *ssd, Posicao *posicao, bool entrar_menu, DADOS_SISTEMA *dados);
void controle_bomba(ssd1306_t *ssd, DADOS_SISTEMA *dados);
#endif
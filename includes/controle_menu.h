#ifndef CONTROLE_MENU_H
#define CONTROLE_MENU_H

#include "pico/stdlib.h"
#include "ssd1306.h"
#include "joystick.h"

void menu_principal(ssd1306_t *ssd, Posicao *posicao);
void nivel_reservatorio(ssd1306_t *ssd);

#endif
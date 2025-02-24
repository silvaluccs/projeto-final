#ifndef JOYSTICK_H
#define JOYSTICK_H

#include "pico/stdlib.h"

typedef struct posicao {
    int x;
    int y;
} Posicao; // estrutura para armazenar a posição do joystick no display

void controle_joystick(Posicao *posicao);

#endif
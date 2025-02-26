#ifndef SETUP_H
#define SETUP_H

#include "pico/stdio.h"
#include "ssd1306.h"

void init_display(ssd1306_t *ssd);
void setup_display();
void setup_botoes(uint pin);
void setup_joystick(uint pino_vrx, uint pino_vry, uint pino_sw);
void setup_led(uint pino);
void setup_matriz_leds(uint pino_matriz_leds);

#endif
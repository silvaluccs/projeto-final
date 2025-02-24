#ifndef SETUP_H
#define SETUP_H

#include "pico/stdio.h"
#include "ssd1306.h"

void init_display(ssd1306_t *ssd);
void setup_display();

#endif
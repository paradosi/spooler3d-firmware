#ifndef SCALE_H
#define SCALE_H

#include <Arduino.h>

void scale_init();
void scale_tare();
float scale_read();
bool scale_ready();

#endif

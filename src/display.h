#ifndef DISPLAY_H
#define DISPLAY_H

#include <Arduino.h>

void display_init();
void display_boot(const char* status);
void display_ready();
void display_weighing(const String &uid);
void display_result(const String &uid, float weight, bool success);
void display_tare();
void display_error(const char* msg);

#endif

#include "scale.h"
#include "config.h"
#include <HX711.h>

static HX711 hx711;

void scale_init() {
    hx711.begin(HX711_DOUT_PIN, HX711_SCK_PIN);
    hx711.set_scale(HX711_CALIBRATION_FACTOR);
    hx711.tare();
    Serial.println("HX711 initialized and tared");
}

void scale_tare() {
    Serial.println("Taring scale...");
    hx711.tare();
    Serial.println("Scale tared");
}

float scale_read() {
    if (!hx711.is_ready()) {
        return -1.0;
    }
    float weight = hx711.get_units(WEIGHT_SAMPLES);
    // Clamp negative values to zero (noise when empty)
    if (weight < 0) weight = 0;
    return weight;
}

bool scale_ready() {
    return hx711.is_ready();
}

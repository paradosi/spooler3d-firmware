#include <Arduino.h>
#include "config.h"
#include "wifi_manager.h"
#include "scale.h"
#include "nfc_reader.h"
#include "display.h"
#include "api_client.h"

static unsigned long lastPoll = 0;
static bool tarePressed = false;
static String lastUid = "";
static unsigned long lastPostTime = 0;

void IRAM_ATTR onTareTouch() {
    tarePressed = true;
}

void setup() {
    Serial.begin(115200);
    Serial.println();
    Serial.println("=== Spooler3D Firmware ===");

    // Init display first so we can show boot status
    display_init();
    display_boot("Starting...");

    // WiFi
    display_boot("Connecting WiFi...");
    wifi_init();
    if (wifi_connected()) {
        display_boot("WiFi connected");
    } else {
        display_boot("WiFi failed - retry");
    }
    delay(500);

    // Scale
    display_boot("Init scale...");
    scale_init();
    delay(200);

    // NFC
    display_boot("Init NFC...");
    nfc_init();
    delay(200);

    // Tare button interrupt
    pinMode(TOUCH_PIN, INPUT);
    attachInterrupt(digitalPinToInterrupt(TOUCH_PIN), onTareTouch, RISING);

    display_ready();
    Serial.println("Setup complete — ready");
}

void loop() {
    // Check WiFi health
    wifi_check();

    // Handle tare button
    if (tarePressed) {
        tarePressed = false;
        scale_tare();
        display_tare();
        delay(1500);
        display_ready();
        return;
    }

    // Poll NFC at interval
    unsigned long now = millis();
    if (now - lastPoll < NFC_POLL_INTERVAL) return;
    lastPoll = now;

    // Debounce: don't re-read the same tag within cooldown
    String uid;
    if (!nfc_read_uid(uid)) return;

    if (uid == lastUid && (now - lastPostTime < POST_COOLDOWN)) {
        return; // Same tag still present, skip
    }

    // Tag detected — weigh and send
    display_weighing(uid);

    if (!scale_ready()) {
        display_error("Scale not ready");
        delay(2000);
        display_ready();
        return;
    }

    float weight = scale_read();
    Serial.print("Weight: ");
    Serial.print(weight, 1);
    Serial.println("g");

    if (!wifi_connected()) {
        display_result(uid, weight, false);
        display_error("No WiFi");
        delay(2000);
        display_ready();
        return;
    }

    bool success = api_post_weight(uid, weight);
    display_result(uid, weight, success);

    lastUid = uid;
    lastPostTime = millis();

    delay(POST_COOLDOWN);
    display_ready();
}

#include "display.h"
#include "config.h"
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

static Adafruit_SSD1306 oled(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);
static bool displayReady = false;

void display_init() {
    if (!oled.begin(SSD1306_SWITCHCAPVCC, OLED_ADDR)) {
        Serial.println("SSD1306 not found");
        displayReady = false;
        return;
    }
    displayReady = true;
    oled.clearDisplay();
    oled.setTextColor(SSD1306_WHITE);
    oled.display();
    Serial.println("SSD1306 initialized");
}

static void clear() {
    if (!displayReady) return;
    oled.clearDisplay();
    oled.setCursor(0, 0);
}

void display_boot(const char* status) {
    clear();
    oled.setTextSize(1);
    oled.println("Spooler3D");
    oled.println();
    oled.println(status);
    oled.display();
}

void display_ready() {
    clear();
    oled.setTextSize(1);
    oled.println("Spooler3D");
    oled.println();
    oled.setTextSize(1);
    oled.println("Ready");
    oled.println();
    oled.println("Place spool on scale");
    oled.println("and tap NFC tag");
    oled.display();
}

void display_weighing(const String &uid) {
    clear();
    oled.setTextSize(1);
    oled.println("Reading...");
    oled.println();
    oled.print("Tag: ");
    // Show truncated UID to fit screen
    if (uid.length() > 10) {
        oled.println(uid.substring(0, 10) + "..");
    } else {
        oled.println(uid);
    }
    oled.println();
    oled.println("Weighing...");
    oled.display();
}

void display_result(const String &uid, float weight, bool success) {
    clear();
    oled.setTextSize(1);

    if (success) {
        oled.println("Sent!");
    } else {
        oled.println("SEND FAILED");
    }

    oled.println();

    // Show weight large
    oled.setTextSize(2);
    oled.print(weight, 1);
    oled.println("g");

    oled.setTextSize(1);
    oled.println();
    oled.print("Tag: ");
    if (uid.length() > 10) {
        oled.print(uid.substring(0, 10) + "..");
    } else {
        oled.print(uid);
    }

    oled.display();
}

void display_tare() {
    clear();
    oled.setTextSize(1);
    oled.println("Spooler3D");
    oled.println();
    oled.setTextSize(2);
    oled.println("TARE");
    oled.setTextSize(1);
    oled.println();
    oled.println("Scale zeroed");
    oled.display();
}

void display_error(const char* msg) {
    clear();
    oled.setTextSize(1);
    oled.println("ERROR");
    oled.println();
    oled.println(msg);
    oled.display();
}

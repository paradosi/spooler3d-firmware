#ifndef CONFIG_H
#define CONFIG_H

// WiFi
#define WIFI_SSID "your-ssid"
#define WIFI_PASS "your-password"

// Spooler3D API
#define API_BASE_URL "http://10.10.10.112:8081"

// HX711 pins
#define HX711_DOUT_PIN 16
#define HX711_SCK_PIN 4

// HX711 calibration factor — tune with a known weight
// Place a known weight (e.g. 500g), read raw value, calculate:
// calibration_factor = raw_reading / known_weight_grams
#define HX711_CALIBRATION_FACTOR 420.0

// TTP223 touch button
#define TOUCH_PIN 15

// I2C (shared by PN532 and SSD1306)
#define I2C_SDA 21
#define I2C_SCL 22

// OLED
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_ADDR 0x3C

// NFC polling interval (ms)
#define NFC_POLL_INTERVAL 500

// Weight reading: number of samples to average
#define WEIGHT_SAMPLES 10

// Cooldown after successful POST (ms)
#define POST_COOLDOWN 3000

#endif

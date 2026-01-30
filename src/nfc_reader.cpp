#include "nfc_reader.h"
#include "config.h"
#include <Wire.h>
#include <Adafruit_PN532.h>

static Adafruit_PN532 nfc(I2C_SDA, I2C_SCL);
static bool nfcReady = false;

void nfc_init() {
    nfc.begin();

    uint32_t versiondata = nfc.getFirmwareVersion();
    if (!versiondata) {
        Serial.println("PN532 not found — check wiring");
        nfcReady = false;
        return;
    }

    Serial.print("PN532 firmware: ");
    Serial.print((versiondata >> 24) & 0xFF);
    Serial.print(".");
    Serial.println((versiondata >> 16) & 0xFF);

    nfc.SAMConfig();
    nfcReady = true;
    Serial.println("PN532 initialized");
}

bool nfc_read_uid(String &uid) {
    if (!nfcReady) return false;

    uint8_t uidBuf[7];
    uint8_t uidLength;

    // Non-blocking read with short timeout
    bool success = nfc.readPassiveTargetID(PN532_MIFARE_ISO14443A, uidBuf, &uidLength, 200);

    if (!success) return false;

    // Format UID bytes as lowercase hex string
    uid = "";
    for (uint8_t i = 0; i < uidLength; i++) {
        if (uidBuf[i] < 0x10) uid += "0";
        uid += String(uidBuf[i], HEX);
    }
    uid.toLowerCase();

    Serial.print("NFC tag UID: ");
    Serial.println(uid);

    return true;
}

#ifndef NFC_READER_H
#define NFC_READER_H

#include <Arduino.h>

void nfc_init();
bool nfc_read_uid(String &uid);

#endif

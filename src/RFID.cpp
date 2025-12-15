#include "RFID.h"

RFID::RFID(uint8_t ssPin, uint8_t rstPin)
    : _ssPin(ssPin),
      _rstPin(rstPin),
      mfrc522(ssPin, rstPin) {}

void RFID::begin() {
    // ESP32 SPI pins: SCK=18, MISO=19, MOSI=23, SS=_ssPin
    SPI.begin(18, 19, 23, _ssPin);
    mfrc522.PCD_Init();
}

Card RFID::get_ID() {
  Card new_card;

  new_card.id_size = mfrc522.uid.size;
  memcpy(new_card.id, mfrc522.uid.uidByte, new_card.id_size);

  return new_card;
}

bool RFID::is_read() {
  if (!mfrc522.PICC_IsNewCardPresent()) return false;
  if (!mfrc522.PICC_ReadCardSerial()) return false;

  return true;
}

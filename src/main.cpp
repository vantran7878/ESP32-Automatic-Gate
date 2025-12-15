#include <Arduino.h>
#include <ArduinoJson.h>
#include "SystemConfig.h"

#include "RFID.h"
#include "Gate.h"
#include "Led.h"
#include "Buzzer.h"
#include "Ultrasonic.h"

SystemConfig g_config;

RFID rfid(5, 22);
Gate gate(26);
Led led(32, 33);


void parseSystemJson(const char* json) {
    StaticJsonDocument<256> doc;
    deserializeJson(doc, json);

    g_config.system_state = (general_state)doc["system"]["status"].as<int>();
    g_config.rfid       = doc["devices"]["rfid"] | g_config.rfid;
    g_config.servo      = doc["devices"]["servo"] | g_config.servo;
}


void setup() {
  Serial.begin(115200);
  rfid.begin();
  gate.attach();
  
  delay(500);
  Serial.println("ESP32 SERIAL OK");
  g_config.system_state = state_normal;
  
}

void loop() {
  Serial.println(1);
  switch(g_config.system_state) {
    case state_normal: {
      Serial.println(2);
      if (rfid.is_read())  {
        Card new_card = rfid.get_ID();
        new_card.print_id();
        gate.open();
        led.light_green();
        delay(3000);
      }
      else {
        gate.close();
        led.light_red();
      }

    }
    break;

    case state_always_open: {
      gate.open();
      led.light_green();
    }
    break;

    case state_always_close: {
      gate.close();
      led.light_red();
    }
    break;

    default:
    break;
  }
  
}

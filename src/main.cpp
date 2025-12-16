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
Led led(33, 32);
Ultrasonic ultra(12, 13);
Buzzer buzzer(21);


//void parseSystemJson(const char* json) {
//    StaticJsonDocument<256> doc;
//    deserializeJson(doc, json);
//
//    g_config.system_state = (general_state)doc["system"]["status"].as<int>();
//    g_config.rfid       = doc["devices"]["rfid"] | g_config.rfid;
//    g_config.servo      = doc["devices"]["servo"] | g_config.servo;
//}


void setup() {
  Serial.begin(115200);
  rfid.begin();
  gate.attach();
  ultra.init();
  buzzer.init();
  led.init();
  
  delay(500);
  Serial.println("ESP32 SERIAL OK");
  g_config.system_state = state_normal;
  gate.close();
  
}

void procedure_open_gate() {
  Card new_card = rfid.get_ID();
  new_card.print_id();

  gate.open();
  led.light_green();
  buzzer.low_pitch(100);
  gate.state = GATE_OPEN;
  gate.timer = millis();
  delay(1000);
}

void procedure_close_gate() {
  gate.close();
  led.no_light();
  gate.state = GATE_CLOSED;
}

void loop() {
  switch(g_config.system_state) {
    case state_normal: {
      Serial.println(ultra.get_distance());
      if (rfid.is_read())  {
        if (gate.state == GATE_CLOSED) {
          Serial.println("open");
          procedure_open_gate();
        }
      }
      else {
        Serial.print("Time: ");
        Serial.println(millis() - gate.timer);
        if (gate.state == GATE_OPEN_ANGLE && millis() - gate.timer >= 1000) {
          Serial.print("start close");
          procedure_close_gate();
        }

        if (ultra.is_violate()) {
          Serial.println("Violate");
          buzzer.high_pitch(100);  
          led.light_red();
          delay(200);
          led.no_light();
        }
        procedure_close_gate();
      }
    }
    break;

    case state_always_open: {
      Serial.println("Always open");
      gate.open();
      led.light_green();
    }
    break;

    case state_always_close: {
      Serial.println("Always close");
      gate.close();
      led.light_red();
      if (rfid.is_read()) {
        buzzer.low_pitch(1000);
      }
      if (ultra.is_violate()) {
        buzzer.high_pitch(1000);
      }
    }
    break;

    default:
    break;
  }
  
}

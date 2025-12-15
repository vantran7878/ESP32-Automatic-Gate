#include "SystemConfig.h"

void SystemConfig::normal_run() {
  system_state = state_normal;
  rfid = 1;
  ultrasonic = 1;
  buzzer = 1;
  servo = 1;
  camera = 1;
  led = 1;
}
void SystemConfig::always_open_run() {
  system_state = state_always_open;
  rfid = 0;
  ultrasonic = 0;
  buzzer = 0;
  servo = 1;
  camera = 0;
  led = 1;
}

void SystemConfig::always_close_run() {
  system_state = state_always_close;
  rfid = 0;
  ultrasonic = 1;
  buzzer = 1;
  servo = 1;
  camera = 1;
  led = 1;
}
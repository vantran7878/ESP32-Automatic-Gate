#include <ESP32Servo.h>

struct Gate {
  int pin;
  Servo servo;
  Gate(int pin);
  void attach();
  void open();
  void close();
};
#include <ESP32Servo.h>

const int GATE_OPEN_DURATION = 1000;
const int GATE_OPEN_ANGLE = 90;
const int GATE_CLOSE_ANGLE = 0;

enum GATE_STATE {
  GATE_CLOSED,
  GATE_OPEN,
};

struct Gate {
  int pin;
  int angle;
  GATE_STATE state;
  unsigned long timer;

  Servo servo;
  Gate(int pin);
  void attach();
  void open();
  void close();
};
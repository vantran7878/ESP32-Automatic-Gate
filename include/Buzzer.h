#include <Arduino.h>

typedef void (Buzzer::*PitchFunc)(int);

struct Buzzer {
  int pin;

  Buzzer(int pin);
  void init();
  void high_pitch(int duration);
  void low_pitch(int duration);
  void no_sound();

};
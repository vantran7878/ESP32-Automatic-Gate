#include "Buzzer.h"

Buzzer::Buzzer(int pin):pin(pin) {}

void Buzzer::init() {
  pinMode(pin, OUTPUT);
}

void Buzzer::high_pitch(int duration) {
  tone(pin, 1000, duration);
}

void Buzzer::low_pitch(int duration) {
  tone(pin, 1000, duration);
}

void Buzzer::no_sound() {
  noTone(pin);
}


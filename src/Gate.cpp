#include "Gate.h"

Gate::Gate(int pin):pin(pin) {
}

void Gate::attach() {
  servo.attach(pin);
}

void Gate::open() {
  servo.write(90);
}

void Gate::close() {
  servo.write(0);
}


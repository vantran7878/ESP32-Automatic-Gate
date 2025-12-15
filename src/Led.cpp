#include <Arduino.h>
#include "Led.h"
Led::Led(int red, int green): red_pin(red), green_pin(green) {}

void Led::init() {
  pinMode(red_pin, OUTPUT);
  pinMode(green_pin, OUTPUT);
}

void Led::light_red() {
  if (activate) digitalWrite(red_pin, HIGH);
  digitalWrite(red_pin, LOW);
} 

void Led::light_green() {
  if (activate) digitalWrite(green_pin, HIGH);
  digitalWrite(green_pin, LOW);
} 

void Led::no_light() {
  digitalWrite(red_pin, LOW);
  digitalWrite(green_pin, LOW);
}

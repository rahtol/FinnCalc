#include <Arduino.h>
#include "keypad.h"
#include <U8x8lib.h>
#include "GraphicsTest.h"
#include "display.h"
#include "calculator.h"

uint8_t rowPins[] = {13, 12, 32, 33};
uint8_t colPins[] = {25, 26, 27, 14};

Ckeypad keypad(rowPins, colPins);
Cdisplay display;
Ccalculator calc;

void setup() {
  Serial.begin(115200);
  keypad.setup();
  display.setup();
  display.setCalculation(calc.getExpression());
  display.setSolution(calc.getResult());
  

}

void loop() {
  char c;
  keypad.loop();
  if(keypad.getChar(c)) {
    Serial.printf("button pressed: %c \n", c);
    calc.process(c);
    display.setCalculation(calc.getExpression());
    display.setSolution(calc.getResult());
  }

  display.loop();

  // GraphicsTestloop();

}


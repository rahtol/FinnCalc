#include "keypad.h"

char decode_array[4][4] = {{'1', '2', '3', 'A'}, {'4', '5', '6', 'B'}, 
                         {'7', '8', '9', 'C'}, {'*', '0', '#', 'D'}};
Ckeypad::Ckeypad (uint8_t *rowPins, uint8_t *colPins) {
    for (int i = 0; i<4; i++) {
        this ->rowPins[i] = rowPins[i];
        this ->colPins[i] = colPins[i];
    }
    currentCol = 0; 
    last_millis = 0;
    last_millis_keypress = 0;
    current_char = '\0';
    current_char_valid = false;
}

void Ckeypad::setup() {
    for (int i = 0; i<4; i++) {
        pinMode(rowPins[i], INPUT_PULLDOWN);
        pinMode(colPins[i], OUTPUT);
    }

    digitalWrite(colPins[currentCol], HIGH);
}

void Ckeypad::loop() {
    uint32_t current = millis();
    if (current - last_millis > 20) {
      last_millis = current;
      for (int row = 0; row<4; row++) {
        if (digitalRead(rowPins[row]) == HIGH) {
            if(current - last_millis_keypress > 500) {
                last_millis_keypress = current;
                current_char = decode(row, currentCol);
                current_char_valid = true;
            }
        }
      }
      digitalWrite(colPins[currentCol], LOW);
      currentCol = (currentCol + 1) % 4;
      digitalWrite(colPins[currentCol], HIGH);
    }
}

bool Ckeypad::getChar(char &c){
    if (current_char_valid) {
        c = current_char;
        current_char_valid  = false;
        return true;
    }
    return false;
}

char Ckeypad::decode(uint8_t row, uint8_t col){
    return decode_array[row][col];
}

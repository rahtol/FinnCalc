#include <Arduino.h>

class Ckeypad {
    public:
        Ckeypad (uint8_t *rowPins, uint8_t *colPins);
        void loop();
        void setup();
        bool getChar(char &c); // return true if charakter read from keypad
    private:
        uint8_t rowPins[4];
        uint8_t colPins[4];
        uint8_t currentCol;
        uint32_t last_millis;
        uint32_t last_millis_keypress;
        char current_char;
        bool current_char_valid;

        char decode(uint8_t row, uint8_t col);
};
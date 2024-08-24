#include <Arduino.h>
#include <U8x8lib.h>

#ifdef U8X8_HAVE_HW_SPI
#include <SPI.h>
#endif
#ifdef U8X8_HAVE_HW_I2C
#include <Wire.h>
#endif

class Cdisplay {
    public:
        Cdisplay();
        void setup();
        void loop();
        void setCalculation(const char *calculation);
        void setSolution(float solution);
    private:
        char *calculation;
        float solution;
        U8X8_SSD1306_128X64_NONAME_HW_I2C u8x8; 	  
};
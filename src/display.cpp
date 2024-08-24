#include <Arduino.h>
#include <U8x8lib.h>
#include <display.h>

Cdisplay::Cdisplay() : u8x8(/* reset=*/ U8X8_PIN_NONE){}
void Cdisplay::setup() {
    u8x8.begin();
}

void Cdisplay::loop() {}

void Cdisplay::setCalculation(const char *calculation) {
  u8x8.setFont(u8x8_font_amstrad_cpc_extended_f);    
  u8x8.setCursor(0,0);
  u8x8.clearLine(0);
  u8x8.print(calculation);
}
void Cdisplay::setSolution(float solution) {
    int digits = (int) ceilf(log10(abs(solution)));

    char buf[32], buf2[32];
    sprintf(buf, "%8.*f", 6-digits, solution);

    int idx;
    for (idx=strlen(buf);  idx > 1 && ((buf[idx-1] == '0')||(buf[idx-1] == '.')); idx--);
    buf[idx] = 0;
    sprintf(buf2, "%8s", buf);

    u8x8.draw2x2String(0, 5, buf2);
}
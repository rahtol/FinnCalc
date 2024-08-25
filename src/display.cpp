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
    int total_places = 8; // eight characters of size 2x2 fit on the line
    int digits_before_decimal_point = max(1, ((int) floorf(log10(abs(solution))) + 1)); // always at least one place before decimal point
    int decimal_places = total_places - 2 - digits_before_decimal_point; // the two account for a sign and the decimal separator 
    // TODO: NaN if decima places < 0

    char buf[32], buf2[32];
    sprintf(buf, "%8.*f", decimal_places, solution);

    if (strchr(buf, '.')) {
      int idx;
      for (idx=strlen(buf);  idx > 1 && (buf[idx-1] == '0'); idx--);
      if (buf[idx-1] == '.') idx--;
      buf[idx] = 0;
      sprintf(buf2, "%8s", buf);
    }
    else {
      strcpy(buf2, buf);
    }

    u8x8.draw2x2String(0, 5, buf2);
}
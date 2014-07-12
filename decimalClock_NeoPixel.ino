#include <Adafruit_NeoPixel.h>
#include <DS1307RTC.h>
#include <Time.h>
#include <Wire.h>

#define NEOPIXEL_PIN 10

Adafruit_NeoPixel strip  = Adafruit_NeoPixel (60, NEOPIXEL_PIN, NEO_RGB + NEO_KHZ800);

uint32_t green = strip.Color(255, 0, 0);
uint32_t red = strip.Color(0, 255, 0);
uint32_t blue = strip.Color(0, 0, 255);

void setup() {
  strip.begin();
  strip.show();
}

void loop() {
  tmElements_t tm;
  if (RTC.read(tm)) {
    int hUnit =tm.Hour%10;
    int hTen = tm.Hour/10;
    int mUnit = tm.Minute%10;
    int mTen = tm.Minute/10;
    int sUnit = tm.Second%10;
    int sTen = tm.Second/10;
    
    displayStrip(hTen, 0, red);
    displayStrip(hUnit, 10, red);
    displayStrip(mTen, 20, green);
    displayStrip(mUnit, 30, green);
    displayStrip(sTen, 40, blue);
    displayStrip(sUnit, 50, blue);  
  }
  else{
    if (RTC.chipPresent()){
      strip.setPixelColor(10, 255, 0, 0);
    } else {
      strip.setPixelColor(10, 0, 0, 255);
    }
    delay(9000);
  }
  delay(1000);
}

void clearStrip(int pin_from){
  for(int i=pin_from; i<=pin_from+9; i++){
    strip.setPixelColor(i, 0, 0, 0);
  }
  strip.show();
}

void displayStrip(int num, int pin_from, uint32_t c){ //take in number, display neopixel accordingly
  if (num == 0){
  clearStrip(pin_from);
  displayStripHelper(num, pin_from, c);
  }
 else displayStripHelper(num, pin_from, c); 
}

void displayStripHelper(int num, int pin_from, uint32_t c){
  for (int i=pin_from; i<=pin_from+num-1; i++){
    strip.begin();
    strip.setPixelColor(i, c);
  }
  strip.show();
    Serial.println("set"); 
}

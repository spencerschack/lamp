#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
  #include <avr/power.h>
#endif

#define PIN 6
#define VARIANCE 10

Adafruit_NeoPixel strip = Adafruit_NeoPixel(144, PIN, NEO_RGBW + NEO_KHZ800);

uint8_t offset;

void setup() {
  offset = 0;
  randomSeed(analogRead(0));
  strip.begin();
  strip.setBrightness(100);
  strip.show();
}

void loop() {
  uint16_t numPixels = strip.numPixels();
  for(uint16_t i = 0; i < numPixels; i++) {
    if(random(3)) {
      strip.setPixelColor(i, 0, random(256), random(256), 0);
    } else {
      strip.setPixelColor(i, 0, 0, 0, 0);
    }
  }
  strip.show();
  delay(1000);
}


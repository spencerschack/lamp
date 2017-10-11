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
  strip.begin();
  strip.setBrightness(100);
  strip.show();
}

void loop() {
  uint16_t numPixels = strip.numPixels();
  uint16_t numHalf = numPixels / 2;
  uint8_t delta;
  for(uint16_t i = 0; i < numPixels; i++) {
    uint16_t index = (i + offset) % numPixels;
    if(index < numHalf) {
      delta = (numHalf - index) * VARIANCE / numHalf;
      strip.setPixelColor(i, 0, delta, 0, 20);
    } else {
      delta = (index - numHalf) * VARIANCE / numHalf;
      strip.setPixelColor(i, 0, 0, delta, 20);
    }
  }
//  if(++offset == numPixels) offset = 0;
  strip.show();
}


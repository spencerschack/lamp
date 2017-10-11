#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
  #include <avr/power.h>
#endif

#define PIN 6
#define PIXELS 144
#define START_LENGTH 1
#define FINISH_LENGTH 15
#define FRAME 17
#define PERIOD 500

Adafruit_NeoPixel strip = Adafruit_NeoPixel(PIXELS, PIN, NEO_RGBW + NEO_KHZ800);
uint32_t drop = strip.Color(0, 0, 30, 30);
uint32_t background = strip.Color(0, 0, 10, 0);

void setup() {
  strip.begin();
  strip.setBrightness(100);
  strip.show();
}

void loop() {
  float delta = powf((float) (millis() % PERIOD) / PERIOD, 3);
  uint16_t length = START_LENGTH + (FINISH_LENGTH - START_LENGTH) * delta;
  uint16_t position = (PIXELS - START_LENGTH - FINISH_LENGTH) * delta;
  for(uint16_t i = 0, l = strip.numPixels(); i < l; i++) {
    uint32_t color = (i >= position && i < position + length) ? drop : background;
    strip.setPixelColor(i, color);
  }
  strip.show();
}

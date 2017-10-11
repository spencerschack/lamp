#include <Adafruit_DotStar.h>
#include <SPI.h>

#define NUM_PIXELS 144
#define EACH(N) for(uint16_t i = 0, l = N; i < l; i++)
Adafruit_DotStar strip = Adafruit_DotStar(NUM_PIXELS, 4, 5, DOTSTAR_BRG);

struct Wave {
  uint16_t from, to;
  unsigned long start;
  uint16_t duration;
};

Wave generate(uint16_t from, unsigned long start) {
  return (Wave) {from, 1/*random(0, 1 << 8)*/, start, 1000/*random(500, 5000)*/};
}

uint16_t color(Wave wave, unsigned long time) {
  float delta = min(((float) (time - wave.start)) / wave.duration, 1.0f);
  return (uint16_t) (((float) wave.from) + delta * ((float) (wave.from - wave.to)));
}

bool replace(Wave wave, unsigned long time) {
  return wave.start + ((unsigned long) wave.duration) > time;
}

struct Wave waves[NUM_PIXELS];

void setup() {
  unsigned long now = millis();
  EACH(NUM_PIXELS) waves[i] = generate(0, now);
  strip.begin();
  strip.show();
}

uint16_t c = 1;

void loop() {
  EACH(NUM_PIXELS) strip.setPixelColor(i, c);
  strip.show();
}

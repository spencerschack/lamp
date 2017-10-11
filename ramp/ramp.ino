#include <Adafruit_DotStar.h>
#include <SPI.h>

#define NUM_PIXELS 144

Adafruit_DotStar strip = Adafruit_DotStar(NUM_PIXELS, 4, 5, DOTSTAR_BRG);
int8_t velocities[NUM_PIXELS];

void setup() {
  strip.begin();
  strip.show();
  randomSeed(analogRead(0));
}

void loop() {
  uint16_t time = (uint16_t) millis() % 10000;
  for(uint16_t i = 0; i < NUM_PIXELS; i++) {
    uint32_t color = strip.getPixelColor(i);
    int8_t velocity = velocities[i];
    if(random(0, 10) == 0)
      velocity = random(0, 3) - 1;
    if(random(0, 10) < 2)
      velocity = 0;
    if(color < 2) velocity = 1;
    if(color == (1 << 3)) velocity = -1;
    if(color > (1 << 3)) color = 1 << 3;
    if(random(0, 250) == 0)
      color = 1 << 4;
    velocities[i] = velocity;
    int8_t height = 0;
    uint16_t peak = time * NUM_PIXELS / 10000;
    float distance = (i - peak) / 50;
    if(distance > -1 && distance < 1) {
//      height = (int8_t) ((cos(distance * PI) + 1) / 2 * 5);
    }
    strip.setPixelColor(i, ((int32_t) color) + velocity + height);
  }
  strip.show();
  delay(1000 / 60);
}

#include "dotstar.h"
#include <array>
#include <math.h>

const uint16_t pixels = 71;
const double tau = 6.283185307179586;

Adafruit_DotStar strip(pixels, A0, A1, DOTSTAR_BRG);

void setup() {
  randomSeed(analogRead(0));
  strip.begin();
  strip.show();
}

double sin11(double input) {
  return sin(input * tau);
}

double sin01(double input) {
  return (sin11(input) + 1) / 2;
}

double sweep(
  double index,
  double time, double duration,
  double period, double length) {

  double distance = length + 2 * period;
  double factor = (time / duration * distance - index) / period;
  return min(1, max(0, factor));
}

double wave(
  double index,
  double time, double duration, double interval,
  double period, double length) {

  double factor = sweep(index, fmod(time, interval), duration, period, length);
  return (sin(factor * tau - tau / 4) + 1) / 2;
}

double profile(double input) {
  if(input > 0.99) return input;
  if(input > 0.95) return input / 2;
  return input / 4;
}

uint32_t flame(double i, double time) {
  return 50 * profile(
    sweep(i, time, 5, 60, pixels) * (
      0.15 * sin01(i / 20 + time / 3) +
      0.4 *  sin01(-i / 40 + time / 10) +
      0.15 * sin01(-i / 4 + time / 1.5) +
      0.15 * wave(i,  time, 2, 5, 20, pixels) +
      0.15 * wave(-i, time, 3, 3, 40, pixels)
    )
  );
}

uint32_t flicker(double i, double time) {
  return 50 * sweep(i, time, 5, 60, pixels) * (
    0.4 * sin01(i / 55 + time / 3) * sin01(-i / 20 + time) +
    0.4 * sin01(-i / 35 + time / 0.75) * sin01(i / 30 + 2 * time) +
    0.2 * sin01(-i / 20 + time / 0.35) * sin01(i / 10 + time / 0.15)
  );
}

uint32_t froth(double i, double time) {
  return 50 * sweep(i, time, 5, 60, pixels) * (
    // lower frequency
    0.5 * sin01(
      (i // index input
          +
        ( // phase
          15 * sin11(time / 15)
        )
      )
        /
      ( // wavelength
        5
          +
        30 * sin01(time / 15)
      )
    )
      +
    // higher frequency
    0.5 * sin01(
      (i // index input
          +
        ( // phase
          10 * sin11(time / 8)
        )
      )
        /
      ( // wavelength
        3
          +
        20 * sin01(time / 4)
      )
    )
  );
}

uint32_t beta(double i, double time) {
  return 20 * sweep(i, time, 5, 60, pixels) * (
    0.3 * sin01(time + i / 20) +
    0.3 * sin01(time / 2 + -i / 40) +
    0.3 * sin01(-time / 3 + -i / 30) +
    0.3 * sin01(time / 5 + i / 50)
  );
}

void loop() {
  static uint32_t first = millis();
  double time = (double) (millis() - first) / 1000;
  for(uint16_t i = 0, ri = pixels - 1; i < pixels; i++, ri--) {
    strip.setPixelColor(i, beta(i, time));
  }
  strip.show();
}

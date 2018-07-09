#include "dotstar.h"
#include <array>
#include <math.h>

#define GAIN 100

const uint16_t pixels = 265;
const float tau = 6.283185307179586;

Adafruit_DotStar left(pixels, D2, D3, DOTSTAR_BRG);
Adafruit_DotStar right(pixels, D4, D5, DOTSTAR_BRG);

void setup() {
  randomSeed(analogRead(0));
  left.begin();
  right.begin();
  left.show();
  right.show();
}

float sin11(float input) {
  return sin(input * tau);
}

float sin01(float input) {
  return (sin11(input) + 1) / 2;
}

float sweep(
  float index,
  float time, float duration,
  float period, float length) {

  float distance = length + 2 * period;
  float factor = (time / duration * distance - index) / period;
  return min(1, max(0, factor));
}

float wave(
  float index,
  float time, float duration, float interval,
  float period, float length) {

  float factor = sweep(index, fmod(time, interval), duration, period, length);
  return (sin(factor * tau - tau / 4) + 1) / 2;
}

float profile(float input) {
  if(input > 0.99) return input;
  if(input > 0.95) return input / 2;
  return input / 4;
}

uint32_t flame(float i, float time) {
  return GAIN * profile(
	sweep(i, time, 5, 60, pixels) * (
	  0.15 * sin01(i / 20 + time / 3) +
	  0.4 *  sin01(-i / 40 + time / 10) +
	  0.15 * sin01(-i / 4 + time / 1.5) +
	  0.15 * wave(i,  time, 2, 5, 20, pixels) +
	  0.15 * wave(-i, time, 3, 3, 40, pixels)
	)
  );
}

uint32_t flicker(float i, float time) {
  return GAIN * sweep(i, time, 5, 60, pixels) * (
	1 * sin01(i / 55 + time / 3) * sin01(-i / 20 + time) +
	0.0 * sin01(-i / 35 + time / 0.75) * sin01(i / 30 + 2 * time) +
	0.0 * sin01(-i / 20 + time / 0.35) * sin01(i / 10 + time / 0.15)
  );
}

uint32_t froth(float i, float time) {
  return GAIN * sweep(i, time, 5, 60, pixels) * (
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

uint32_t beta(float i, float time) {
  return GAIN * sweep(i, time, 5, 60, pixels) * (
	0.25 * sin01(time + i / 20) +
	0.25 * sin01(time / 2 + -i / 40) +
	0.25 * sin01(-time / 3 + -i / 30) +
	0.25 * sin01(time / 5 + i / 50)
  );
}

uint8_t pulseWidth = 30;
uint32_t ember(float i, float time) {
    return GAIN * sweep(i, time, 5, 60, pixels) *
    // sin01(i / 55 + time / 3);
    // sin01(-i / pulseWidth + time);


    // return i*10*sin01(time);

    100*sin01(i*i/3 + i/10 + time);
}

uint32_t ember2(float i, float time) {
    return .8*GAIN * (
            sin01(i*i/3 + i/10 + time)
            // * sin01(-time / 4 + i / 35)
        )
        // +
        // 1/8 * beta(i, time)
        // +
        // GAIN / 2 * (
        //     (i/pixels)
        //     * sin01(time/7)
        //     // * sin01(2*time)
        // )
        -
        GAIN / 2 * (
            (i / pixels)
            * sin01(time/5)
            * sin01(time/3)
        )
        -
        GAIN / 4 * (
            (i/pixels * i/pixels)
            * sin01(time/4)
            // * sin01(time)
        )
        -
        GAIN / 8 * (
            (i / pixels) *
            sin01(2*time)
        );
}

void loop() {
  static uint32_t first = millis();
  float time = (float) (millis() - first) / 1000;

  for(uint16_t i = 0, ri = pixels - 1; i < pixels; i++, ri--) {
		  left.setPixelColor(i, ember2(i, time));
		  right.setPixelColor(i, ember2(i, time));
  }

  left.show();
  right.show();
}

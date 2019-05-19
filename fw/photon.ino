#include <array>
#include <math.h>
#include "dotstar.h"
#include "sinLookupTable.h"

SYSTEM_MODE(SEMI_AUTOMATIC)
SYSTEM_THREAD(ENABLED)

#define RETRY_TIMEOUT_MS        60000
#define STOP_CONNECT_TIME_MS    30000
#define PIXELS                    265
#define GAIN                      100

Timer retryTimer(RETRY_TIMEOUT_MS, attemptRetry);  // timer to retry connecting
Timer stopTimer(STOP_CONNECT_TIME_MS, DisableWiFi);     // timer to stop a long running try
Adafruit_DotStar left(PIXELS, D2, D3, DOTSTAR_BRG);
Adafruit_DotStar right(PIXELS, D4, D5, DOTSTAR_BRG);

static bool attemptingRetry = false;

void attemptRetry()
{
  if (!Particle.connected()) {
    Serial.println("Enabling WiFi");
    stopTimer.start();         // set of the timout time
    WiFi.on();
    Particle.connect();        // start a reconnection attempt
  } else {
    Serial.println("Connected");
    retryTimer.stop();         // no further attempts required
    attemptingRetry = false;
  }
}

void DisableWiFi()
{
    Serial.println("Disabling WiFi");
    if (!Particle.connected()) {
        WiFi.off();
    }
    stopTimer.stop();
}

void wifiService()
{
  if (!attemptingRetry && !Particle.connected()) {
    Serial.println("Attempting retry");
    attemptingRetry = true;
    stopTimer.start();  // set timeout for auto-retry by system
    retryTimer.start(); // schedula a retry
  }
}

float sinFn(float input) {
    return (sinLookupTable[ ((int) (1024 * input)) % 1024 ]);
}

float ignite(
  float index,
  float t, float duration,
  float period, float length) {

  float distance = length + 2 * period;
  float factor = (t / duration * distance - index) / period;
  return min(1, max(0, factor));
}

uint32_t ember2(float i, float t) {
    return (.8*GAIN) * ignite(i, t, 5, 60, PIXELS) * (
            sinFn(i*i/3 + i/10 + t)
        )
        -
        GAIN / 2 * (
            (i / PIXELS)
            * sinFn(t/5)
            * sinFn(t/3)
        )
        -
        GAIN / 4 * (
            (i/PIXELS * i/PIXELS)
            * sinFn(t/4)
        )
        -
        GAIN / 16 * (
            (i / PIXELS)
            * sinFn(2*t)
        )

        -
        GAIN /16 * (
            (i / PIXELS)
            * sinFn(4*t)
        );
}

void ledService()
{
  // led service
  static uint32_t first = millis();
  float t = (float) (millis() - first) / 1000;

  for(uint16_t i = 0, ri = PIXELS - 1; i < PIXELS; i++, ri--) {
      left.setPixelColor(i, ember2(i, t));
    right.setPixelColor(i, ember2(i, t));
  }

  left.show();
  right.show();
}

void setup()
{
  // random init
  randomSeed(analogRead(0));

  // uart init
  Serial.begin(115200);

  // led init
  left.begin();
  right.begin();
  left.show();
  right.show();

  // wifi init
  Particle.connect();
}

void loop()
{
  ledService();
  wifiService();
}

#include "dotstar.h"
#include "color.h"
#include "pixel.h"
#include "strip.h"

#ifndef CONTROLLER_H
#define CONTROLLER_H

class Controller {
  static Adafruit_DotStar left, right;
  static Adafruit_DotStar controller(Strip strip);
public:
  static void set(Pixel pixel, Color color);
  static Color get(Pixel pixel);
  static void begin();
  static void show();
};

#endif

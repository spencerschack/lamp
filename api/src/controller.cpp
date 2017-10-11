#include "controller.h"
#include "strip.h"

Adafruit_DotStar Controller::left = Adafruit_DotStar(Strip::Length, A0, A1, DOTSTAR_BRG);
Adafruit_DotStar Controller::right = Adafruit_DotStar(Strip::Length, A2, A3, DOTSTAR_BRG);
Adafruit_DotStar Controller::controller(Strip strip) {
  return strip.type == Strip::Left ? left : right;
}
void Controller::set(Pixel pixel, Color color) {
  controller(pixel.strip).setPixelColor(pixel.index, color);
}
Color Controller::get(Pixel pixel) {
  return controller(pixel.strip).getPixelColor(pixel.index);
}
void Controller::begin() {
  left.begin();
  right.begin();
}
void Controller::show() {
  left.show();
  right.show();
}

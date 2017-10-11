#include "controller.h"
#include "strip.h"

void Pixel::set(Color color) {
  Controller::set(*this, color);
}
Color Pixel::get() {
  return Controller::get(*this);
}

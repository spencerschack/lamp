#include "Particle.h"
#include "application.h"
#include "lamp.h"
#include "pixel.h"
#include "controller.h"

Lamp lamp;

void render(Pixel pixel) {
  pixel.set(1);
}

void setup() {
  Controller::begin();
}

void loop() {
  Pixel pixel(Strip::Left, DirectionGroup::First, LightingGroup::First, Index::First, Position(0, 0, 0));
  pixel.set(1);
  Controller::show();
}

#include "strip.h"
#include "index.h"
#include "color.h"
#include "position.h"
#include "lighting_group.h"
#include "direction_group.h"

#ifndef PIXEL_H
#define PIXEL_H

class Pixel {
public:
  Pixel(
    Strip strip,
    DirectionGroup directionGroup,
    LightingGroup lightingGroup,
    Index index,
    Position position
  ) :
    strip(strip),
    directionGroup(directionGroup),
    lightingGroup(lightingGroup),
    index(index),
    position(position)
  {};
  Strip strip;
  DirectionGroup directionGroup;
  LightingGroup lightingGroup;
  Index index;
  Position position;

  void set(Color color);
  Color get();
};

#endif

#include "direction.h"

#ifndef POSITION_H
#define POSITION_H

class Position {
public:
  float x, y, z;
  Position(float x, float y, float z) : x(x), y(y), z(z) {};
  Position operator+(Direction direction);
};

#endif

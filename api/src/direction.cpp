#include "direction.h"

Direction Direction::operator*(float c) {
  return Direction(c * x, c * y, c * z);
};

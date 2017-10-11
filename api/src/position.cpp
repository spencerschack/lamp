#include "position.h"

Position Position::operator+(Direction direction) {
  return Position(direction.x + x, direction.y + y, direction.z + z);
};

#include "direction_group.h"

const DirectionGroup::TypeList DirectionGroup::lengths = {
  10, 10, 10, 10, 10, 10, 10
};

const DirectionGroup::TypeList DirectionGroup::offsets = []{
  Index offset = 0;
  TypeList offsets = { 0, 0, 0, 0, 0, 0, 0 };
  for(uint8_t i = 0; i < lengths.size(); i++) {
    offsets[i] = offset;
    offset += lengths[i];
  }
  return offsets;
}();

const DirectionGroup::DirectionList DirectionGroup::directions = {
  Direction(0, 0, 20),
  Direction(-6, 0, 0),
  Direction(0, 0, 12),
  Direction(12, 0, 0),
  Direction(0, 0, 12),
  Direction(-6, 0, 0),
  Direction(-6, 0, 18)
};

const DirectionGroup::PositionList DirectionGroup::positions = []{
  Position position(0, 0, 0);
  PositionList positions = {
    Position(0, 0, 0),
    Position(0, 0, 0),
    Position(0, 0, 0),
    Position(0, 0, 0),
    Position(0, 0, 0),
    Position(0, 0, 0),
    Position(0, 0, 0)
  };
  for(uint8_t i = 0; i < lengths.size(); i++) {
    positions[i] = position;
    position = position + directions[i];
  }
  return positions;
}();

DirectionGroup DirectionGroup::next() {
  return DirectionGroup((Type) ((type + 1) % (Top + 1)));
}

Index DirectionGroup::length() {
  return lengths[type];
}

Index DirectionGroup::offset() {
  return offsets[type];
}

Position DirectionGroup::position() {
  return positions[type];
}

Direction DirectionGroup::direction() {
  return directions[type];
}

Position DirectionGroup::position(Index index) {
  float amount = ((float) (index - offset())) / length();
  Position base = position();
  Direction diff = direction();
  return base + (diff * amount);
}

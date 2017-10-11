#include "group.h"
#include "position.h"
#include "index.h"
#include <array>

#ifndef DIRECTION_GROUP_H
#define DIRECTION_GROUP_H

class DirectionGroup : public Group {
public:
  enum Type : uint8_t {
    Bottom,
    BottomHorizontal,
    BottomVertical,
    Center,
    TopVertical,
    TopHorizontal,
    Top
  };
  typedef std::array<Index, Top + 1> TypeList;
  typedef std::array<Position, Top + 1> PositionList;
  typedef std::array<Direction, Top + 1> DirectionList;
  static const TypeList lengths, offsets;
  static const PositionList positions;
  static const DirectionList directions;
  static const Type First = Bottom;
  Type type;
  DirectionGroup(Type type) : type(type) {};
  DirectionGroup next();
  Index length();
  Index offset();
  Position position();
  Direction direction();
  Position position(Index index);
};

#endif

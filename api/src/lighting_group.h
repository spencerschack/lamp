#include "group.h"
#include <array>

#ifndef LIGHTING_GROUP_H
#define LIGHTING_GROUP_H

class LightingGroup : public Group {
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
  static const TypeList lengths, offsets;
  static const Type First = Bottom;
  Type type;
  LightingGroup(Type type) : type(type) {};
  Index length();
  Index offset();
  LightingGroup next();
};

#endif

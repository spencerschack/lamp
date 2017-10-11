#include "lighting_group.h"

const LightingGroup::TypeList LightingGroup::lengths = {
  10, 10, 10, 10, 10, 10, 10
};

const LightingGroup::TypeList LightingGroup::offsets = []{
  Index offset = 0;
  TypeList offsets = { 0, 0, 0, 0, 0, 0, 0 };
  for(uint8_t i = 0; i < lengths.size(); i++) {
    offsets[i] = offset;
    offset += lengths[i];
  }
  return offsets;
}();

LightingGroup LightingGroup::next() {
  return LightingGroup((Type) ((type + 1) % (Top + 1)));
}

Index LightingGroup::length() {
  return lengths[type];
}

Index LightingGroup::offset() {
  return offsets[type];
}

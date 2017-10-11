#include <cinttypes>
#include "index.h"
#include "color.h"

#ifndef STRIP_H
#define STRIP_H

class Strip {
public:
  enum Type : uint8_t { Left, Right };
  static const Index Length;

  Type type;

  Strip(Type type) : type(type) {};
};

#endif

#include <cinttypes>

#ifndef INDEX_H
#define INDEX_H

class Index {
  uint16_t index;
public:
  Index(uint16_t index) : index(index) {};
  static const Index First, Last;
  operator uint16_t() const;
  Index operator++();
  Index operator+=(Index other);
};

#endif

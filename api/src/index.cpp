#include "index.h"
#include "strip.h"

const Index Index::First = 0;
const Index Index::Last = Strip::Length;
Index::operator uint16_t() const {
  return index;
};
Index Index::operator++() {
  index++;
  if(index == Index::Last) index = Index::First;
  return *this;
};
Index Index::operator+=(Index other) {
  index += other.index;
  return *this;
};

#ifndef DIRECTION_H
#define DIRECTION_H

class Direction {
public:
  float x, y, z;
  Direction(float x, float y, float z) : x(x), y(y), z(z) {};
  Direction operator*(float c);
};

#endif

#include "pixel.h"

#ifndef LAMP_H
#define LAMP_H

typedef void (RenderFunction)(Pixel);

class Lamp {
public:
  void render(RenderFunction render);
};

#endif

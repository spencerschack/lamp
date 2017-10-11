#include "lamp.h"
#include "controller.h"

void Lamp::render(RenderFunction render) {
  DirectionGroup directionGroup = DirectionGroup::First;
  LightingGroup lightingGroup = LightingGroup::First;

  for(Index index = Index::First; index < Index::Last; ++index) {

    if(index == directionGroup.next().offset())
      directionGroup = directionGroup.next();

    if(index == lightingGroup.next().offset())
      lightingGroup = lightingGroup.next();

    for(Strip strip : { Strip::Left, Strip::Right }) {
      Position position = directionGroup.position(index);
      render(Pixel(
        strip,
        directionGroup,
        lightingGroup,
        index,
        position
      ));
    }
  }
  Controller::show();
}

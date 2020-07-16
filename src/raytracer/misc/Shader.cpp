//
// Created by damian on 10.07.2020.
//

#include "Shader.h"
util::Color rt::Shader::shadeHit(const rt::World &world, const rt::Computations &comps, short callsLeft)
{
  auto color = util::Color::BLACK;
  auto reflectedColor = rt::reflectedColor(world,comps,callsLeft);
  for(const auto &light : world.lights()) {
    bool inShadow = rt::isShadowed(world,comps.overPoint);
    color = color + rt::lighting(comps.object->material(),*comps.object, *light, comps.point, comps.eyev, comps.normalv,inShadow);
  }
  return color + reflectedColor;
}

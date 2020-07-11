//
// Created by damian on 10.07.2020.
//

#include "Shader.h"
util::Color rt::Shader::shadeHit(const rt::World &world, const rt::Computations &comps)
{
  auto color = util::Color::BLACK;
  for(const auto &light : world.lights()) {
    color = color + rt::lighting(comps.object->material(), *light, comps.point, comps.eyev, comps.normalv);
  }
  return color;
}
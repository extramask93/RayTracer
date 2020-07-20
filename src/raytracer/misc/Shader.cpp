//
// Created by damian on 10.07.2020.
//

#include "Shader.h"
util::Color rt::Shader::shadeHit(const rt::World &world, const rt::Computations &comps, short callsLeft)
{
  auto color = util::Color::BLACK;
  for (const auto &light : world.lights()) {
    bool inShadow = rt::isShadowed(world, comps.overPoint);
    color = color + rt::lighting(comps.object->material(), *comps.object, *light, comps.point, comps.eyev, comps.normalv, inShadow);


    auto reflectedColor = rt::reflectedColor(world, comps, callsLeft);
    auto refractedColor = rt::refractedColor(world, comps, callsLeft);
    const rt::Material material = comps.object->material();
    auto dupa= comps.object->material().transparency();
    (void)dupa;
    if (material.reflective() > 0 && material.transparency() > 0) {
      auto reflectance = rt::schlick(comps);
      color = color + reflectedColor * reflectance + refractedColor * (1 - reflectance);
    } else {
      color = color + reflectedColor + refractedColor;
    }
  }
return color;
}

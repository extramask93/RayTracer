//
// Created by damian on 08.07.2020.
//

#include "PointLight.h"

util::Color rt::lighting(const rt::Material &material, const rt::PointLight &light, const util::Tuple &position, const util::Tuple &eye, const util::Tuple &normal)
{
  auto effectiveColor = material.color() * light.intensity();

  //ambient is const
  util::Color ambient = effectiveColor * material.ambient();

  auto lightVector = (light.position() - position).normalize();
  auto light_dot_normal = lightVector.dot(normal);//cos(theta)

  util::Color diffuse(0, 0, 0);
  util::Color specular(0, 0, 0);
  if (light_dot_normal < 0) {
    diffuse = util::Color::BLACK;
    specular = util::Color::BLACK;
  } else {
    diffuse = effectiveColor * material.diffuse() * light_dot_normal;
    auto reflectVector = (-lightVector).reflect(normal);
    auto reflect_dot_eye = reflectVector.dot(eye);
    if (reflect_dot_eye <= 0) {
      specular = util::Color::BLACK;
    } else {
      auto factor = std::pow(reflect_dot_eye, material.shininess());
      specular = effectiveColor * material.specular() * factor;
    }
  }
  return ambient + diffuse + specular;
}

//
// Created by damian on 12.07.2020.
//

#ifndef MYPROJECT_PLANE_H
#define MYPROJECT_PLANE_H

#include "Shape.h"
#include <intersections/Intersections.h>
namespace rt {
class Plane : public Shape
{
public:
  Intersections localIntersect(const Ray &ray) const override;
  util::Tuple localNormalAt(const util::Tuple &point) const override;
  AABB bounds() const override;

};
}// namespace rt


#endif//MYPROJECT_PLANE_H

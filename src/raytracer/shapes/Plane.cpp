//
// Created by damian on 12.07.2020.
//

#include "Plane.h"
#include <misc/Computations.h>
#include <cmath>
rt::Intersections rt::Plane::localIntersect(const rt::Ray &ray) const
{
  if(std::abs(ray.direction().y()) < EPSILON) {
    return  rt::Intersections{};
  } else {
    auto t = -ray.origin().y() / ray.direction().y();
    return rt::Intersections{rt::Intersection(t,this)};
  }
}
util::Tuple rt::Plane::localNormalAt(const util::Tuple &point) const
{
  (void)point;
  return util::Tuple::vector(0,1,0);
}


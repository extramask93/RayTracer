//
// Created by damian on 20.07.2020.
//

#include "Cube.h"
#include <intersections/Intersections.h>
#include <misc/Computations.h>
#include <limits>
rt::Intersections rt::Cube::localIntersect(const rt::Ray &ray) const
{
  auto [xtmin,xtmax] = checkAxis(ray.origin().x(), ray.direction().x());
  auto [ytmin,ytmax] = checkAxis(ray.origin().y(), ray.direction().y());
  auto [ztmin,ztmax] = checkAxis(ray.origin().z(), ray.direction().z());
  auto tmin = std::max({xtmin,ytmin,ztmin});
  auto tmax = std::min({xtmax,ytmax,ztmax});
  return rt::Intersections{rt::Intersection(tmin, this), rt::Intersection(tmax,this)};
}
util::Tuple rt::Cube::localNormalAt(const util::Tuple &point, const rt::Intersection &intersection) const
{
  (void)intersection;
  auto max = std::max({fabs(point.x()),fabs(point.y()),fabs(point.z())});
  if(max == fabs(point.x())) {
    return util::Tuple::vector(point.x(),0,0);
  } else if(max == fabs(point.y())) {
    return util::Tuple::vector(0,point.y(),0);
  } else {
    return util::Tuple::vector(0,0,point.z());
  }
}
std::pair<double, double> rt::Cube::checkAxis(double origin, double direction) const
{
  auto tmin_numerator = (-1 - origin);
  auto tmax_numerator = (1-origin);
  double tmin,tmax;
  if constexpr (std::numeric_limits<double>::is_iec559) {
    tmin = tmin_numerator / direction;
    tmax = tmax_numerator / direction;
  } else {
    if (std::fabs(direction) >= EPSILON) {
      tmin = tmin_numerator / direction;
      tmax = tmax_numerator / direction;
    } else {
      tmin = tmin_numerator * std::numeric_limits<double>::infinity();
      tmax = tmax_numerator * std::numeric_limits<double>::infinity();
    }
  }
  if(tmin > tmax) {
    std::swap(tmin,tmax);
  }
  return std::make_pair(tmin,tmax);
}
rt::AABB rt::Cube::bounds() const
{
  return rt::AABB(util::Tuple::point(-1,-1,-1), util::Tuple::point(1,1,1));
}

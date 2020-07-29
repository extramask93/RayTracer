//
// Created by damian on 21.07.2020.
//

#include "Cone.h"
#include <misc/Computations.h>
#include <intersections/Intersections.h>
rt::Intersections rt::Cone::localIntersect(const rt::Ray &ray) const
{
  auto result = Intersections{};
  auto a = pow(ray.direction().x(), 2) - pow(ray.direction().y(), 2) + pow(ray.direction().z(), 2);
  auto b = 2 * ray.origin().x() * ray.direction().x() - 2 * ray.origin().y() * ray.direction().y() + 2 * ray.origin().z() * ray.direction().z();
  if(fabs(a) < EPSILON && fabs(b) < EPSILON) {
    return result;
  }
  auto c = pow(ray.origin().x(), 2) - pow(ray.origin().y(), 2) + pow(ray.origin().z(), 2) ;
  if(fabs(a) < EPSILON) {
    auto t = -c / (2*b);
    result.emplace_back(Intersection(t,this));
  }
  auto disc = pow(b, 2) - 4 * a * c;
  if (disc < 0) {
    return result;
  }
  auto t0 = (-b - sqrt(disc)) / (2 * a);
  auto t1 = (-b + sqrt(disc)) / (2 * a);
  auto y0 = ray.origin().y() + t0 * ray.direction().y();
  auto y1 = ray.origin().y() + t1 * ray.direction().y();
  if (y0 > m_min && y0 < m_max) {
    result.emplace_back(Intersection(t0, this));
  }
  if (y1 > m_min && y1 < m_max) {
    result.emplace_back(Intersection(t1, this));
  }
  intersectCaps(ray, result);
  return result;
}
util::Tuple rt::Cone::localNormalAt(const util::Tuple &point, const rt::Intersection &intersection) const
{
  (void)intersection;
  auto dist = pow(point.x(),2) + pow(point.z(),2);
  if(dist < 1 && point.y() >= m_max - EPSILON) {
    return util::Tuple::vector(0,1,0);
  } else if(dist < 1 && point.y() <= m_min + EPSILON) {
    return util::Tuple::vector(0,-1,0);
  }
  auto y = sqrt(pow(point.x(),2) + pow(point.z(),2));
  if(point.y() >0) {
    y = -y;
  }
  return util::Tuple::vector(point.x(),y,point.z());

}

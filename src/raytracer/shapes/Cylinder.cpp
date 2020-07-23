//
// Created by damian on 21.07.2020.
//

#include "Cylinder.h"
#include <intersections/Intersections.h>
#include <misc/Computations.h>
rt::Intersections rt::Cylinder::localIntersect(const rt::Ray &ray) const
{
  auto a = pow(ray.direction().x(),2) + pow(ray.direction().z(),2);
  auto result = Intersections{};
  if(std::fabs(a) >= EPSILON) {
    auto b = 2 * ray.origin().x() * ray.direction().x() + 2 * ray.origin().z() * ray.direction().z();
    auto c = pow(ray.origin().x(), 2) + pow(ray.origin().z(), 2) - 1;
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
  }
  intersectCaps(ray,result);
  return result;
}
util::Tuple rt::Cylinder::localNormalAt(const util::Tuple &point) const
{
  auto dist = pow(point.x(),2) + pow(point.z(),2);
  if(dist < 1 && point.y() >= m_max - EPSILON) {
    return util::Tuple::vector(0,1,0);
  } else if(dist < 1 && point.y() <= m_min + EPSILON) {
    return util::Tuple::vector(0,-1,0);
  }
  return util::Tuple::vector(point.x(),0,point.z());
}
double &rt::Cylinder::minimum()
{
  return m_min;
}
const double &rt::Cylinder::minimum() const
{
  return m_min;
}
double &rt::Cylinder::maximum()
{
  return m_max;
}
const double &rt::Cylinder::maximum() const
{
  return m_max;
}
bool &rt::Cylinder::closed()
{
  return  m_closed;
}
const bool &rt::Cylinder::closed() const
{
  return m_closed;
}
bool rt::Cylinder::checkCap(const rt::Ray &ray,double t) const
{
  auto x = ray.origin().x() + t * ray.direction().x();
  auto z = ray.origin().z() + t * ray.direction().z();
  return pow(x,2) + pow(z,2) <= 1;
}
void rt::Cylinder::intersectCaps(const rt::Ray &ray, rt::Intersections &intersections) const
{
  if(!m_closed || fabs(ray.direction().y()) < EPSILON) {
    return;
  }
  auto t = (m_min - ray.origin().y() )/ ray.direction().y();
  if(checkCap(ray,t)) {
    intersections.emplace_back(Intersection(t,this));
  }
  t = (m_max - ray.origin().y() )/ ray.direction().y();
  if(checkCap(ray,t)) {
    intersections.emplace_back(Intersection(t,this));
  }
}
rt::AABB rt::Cylinder::bounds() const
{
  return rt::AABB(util::Tuple::point(-1,m_min,-1), util::Tuple::point(1,m_max,1));
}

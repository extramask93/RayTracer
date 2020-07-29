//
// Created by damian on 28.07.2020.
//

#include "SmoothTriangle.h"
#include <intersections/Intersections.h>
#include <misc/Computations.h>
rt::SmoothTriangle::SmoothTriangle(const util::Tuple &p1, const util::Tuple &p2, const util::Tuple &p3,
  const util::Tuple &n1, const util::Tuple &n2, const util::Tuple &n3) : Triangle(p1,p2,p3), m_n1(n1),m_n2(n2),
                           m_n3(n3)
{
}
const util::Tuple &rt::SmoothTriangle::n1() const
{
  return m_n1;
}
const util::Tuple &rt::SmoothTriangle::n2() const
{
  return m_n2;
}
const util::Tuple &rt::SmoothTriangle::n3() const
{
 return m_n3;
}
rt::Intersections rt::SmoothTriangle::localIntersect(const rt::Ray &ray) const
{
  auto dirCrossE2 = ray.direction().cross(e2());
  auto det = e1().dot(dirCrossE2);
  if(math::absd(det) < EPSILON) {
    return Intersections{};
  }
  auto f = 1.0 /det;
  auto p1ToOrigin = ray.origin() - p1();
  auto u = f * p1ToOrigin.dot(dirCrossE2);
  if(u < 0 || u > 1){
    return Intersections{};
  }
  auto originCrossE1 = p1ToOrigin.cross(e1());
  auto v = f * ray.direction().dot(originCrossE1);
  if(v<0 || (u+v) > 1) {
    return Intersections{};
  }
  auto t = f * e2().dot(originCrossE1);
  return Intersections{Intersection(t,this,u,v)};
}
util::Tuple rt::SmoothTriangle::localNormalAt(const util::Tuple &point, const rt::Intersection &intersection) const
{
  (void)point;
  return m_n2 * intersection.u() + m_n3 * intersection.v() + m_n1 * (1 - intersection.u() - intersection.v());
}

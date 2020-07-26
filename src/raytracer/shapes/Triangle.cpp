//
// Created by damian on 25.07.2020.
//

#include "Triangle.h"
#include <intersections/Intersections.h>
#include <misc/Computations.h>
rt::AABB rt::Triangle::bounds() const
{
  return rt::AABB();
}
rt::Intersections rt::Triangle::localIntersect(const rt::Ray &ray) const
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
  return Intersections{Intersection(t,this)};
}
util::Tuple rt::Triangle::localNormalAt(const util::Tuple &point) const
{
  (void)point;
  return m_normal;
}
rt::Triangle::Triangle(const util::Tuple &p1, const util::Tuple &p2, const util::Tuple &p3) : Shape(), m_p1(p1),
                                                                                              m_p2(p2),
                                                                                              m_p3(p3),
                                                                                              m_e1(m_p2 - m_p1),
                                                                                              m_e2(m_p3-m_p1),
                                                                                              m_normal(m_e2.cross(m_e1).normalization())
{
}
const util::Tuple &rt::Triangle::p1() const
{
  return m_p1;
}
const util::Tuple &rt::Triangle::p2() const
{
  return m_p2;
}
const util::Tuple &rt::Triangle::p3() const
{
  return m_p3;
}
const util::Tuple &rt::Triangle::e1() const
{
  return m_e1;
}
const util::Tuple &rt::Triangle::e2() const
{
  return m_e2;
}
const util::Tuple &rt::Triangle::normal() const
{
  return m_normal;
}

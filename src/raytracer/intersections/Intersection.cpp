//
// Created by damian on 06.07.2020.
//

#include "intersections/Intersection.h"
#include "Intersections.h"
#include <shapes/Shape.h>
namespace rt{

Intersection::Intersection(double t, const Shape * shape, double u, double v):m_shape(shape), m_t(t),
                                                                                        m_u(u),m_v(v)
{
}
bool Intersection::operator==(const Intersection &other) const
{
  return (m_t == other.m_t) && (*m_shape == *other.m_shape);
}
bool Intersection::operator<(const Intersection &other) const
{
  return m_t < other.m_t;
}
const Shape* Intersection::object() const
{
  return m_shape;
}
double Intersection::t() const
{
  return m_t;
}
double Intersection::u() const
{
  return m_u;
}
double Intersection::v() const
{
  return m_v;
}
}
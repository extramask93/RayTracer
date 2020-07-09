//
// Created by damian on 06.07.2020.
//

#ifndef MYPROJECT_INTERSECTION_H
#define MYPROJECT_INTERSECTION_H


#include <initializer_list>
#include <vector>
#include <algorithm>
#include <shapes/Shape.h>
#include <optional>
namespace rt {

class Intersection
{
public:
  constexpr Intersection(double t, const Shape * shape);
  [[nodiscard]] constexpr bool operator==(const Intersection &other) const;
  [[nodiscard]] constexpr bool operator<(const Intersection &other) const;
  [[nodiscard]] constexpr double t() const;
  [[nodiscard]] constexpr const rt::Shape*  object() const;
private:
  const Shape * m_shape;
  double m_t;
};

constexpr Intersection::Intersection(double t, const Shape * shape):  m_shape(shape), m_t(t)
{
}
constexpr bool Intersection::operator==(const Intersection &other) const
{
  return (m_t == other.m_t) && (*m_shape == *other.m_shape);
}
constexpr bool Intersection::operator<(const Intersection &other) const
{
  return m_t < other.m_t;
}
constexpr const Shape* Intersection::object() const
{
  return m_shape;
}
constexpr double Intersection::t() const
{
  return m_t;
}

}


#endif//MYPROJECT_INTERSECTION_H

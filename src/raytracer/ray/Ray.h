//
// Created by damian on 06.07.2020.
//

#ifndef MYPROJECT_RAY_H
#define MYPROJECT_RAY_H
#include <Tuple.h>
#include <Matrix.h>
namespace rt {
class Ray
{
public:
  constexpr Ray(const util::Tuple &origin, const util::Tuple &direction);
  [[nodiscard]] constexpr util::Tuple origin() const;
  [[nodiscard]] constexpr util::Tuple direction() const;
  [[nodiscard]] constexpr util::Tuple position(double t) const;
  [[nodiscard]] constexpr Ray transform(const util::Matrix<double> &m) const;
private:
  util::Tuple m_origin;
  util::Tuple m_direction;
};

constexpr Ray::Ray(const util::Tuple &origin, const util::Tuple &direction)
  : m_origin(origin), m_direction(direction)
{
}
constexpr util::Tuple Ray::origin() const {
  return m_origin;
}

constexpr util::Tuple Ray::direction() const {
  return m_direction;
}
constexpr util::Tuple Ray::position(double t) const
{
  auto traveledDistance = m_direction*t;
  return m_origin + traveledDistance;
}
constexpr Ray Ray::transform(const util::Matrix<double> &m) const
{
  Ray newRay= *this;
  newRay.m_origin = m * m_origin;
  newRay.m_direction = m * m_direction;
  return newRay;
}
}


#endif//MYPROJECT_RAY_H

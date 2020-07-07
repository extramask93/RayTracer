//
// Created by damian on 06.07.2020.
//

#ifndef MYPROJECT_RAY_H
#define MYPROJECT_RAY_H
#include <Tuple.h>
namespace rt {
class Ray
{
public:
  explicit Ray(const util::Tuple &origin, const util::Tuple &direction);
  [[nodiscard]] constexpr util::Tuple origin() const;
  [[nodiscard]] constexpr util::Tuple direction() const;
  [[nodiscard]] constexpr util::Tuple position(double t) const;
private:
  util::Tuple m_origin;
  util::Tuple m_direction;
};

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
}


#endif//MYPROJECT_RAY_H

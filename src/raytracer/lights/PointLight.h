//
// Created by damian on 08.07.2020.
//

#ifndef MYPROJECT_POINTLIGHT_H
#define MYPROJECT_POINTLIGHT_H
#include <Tuple.h>
#include <Color.h>
namespace rt {
class PointLight
{
public:
  constexpr explicit PointLight(util::Tuple position, util::Color color);
  [[nodiscard]] constexpr util::Tuple position() const;
  [[nodiscard]] constexpr util::Color intensity() const;

private:
  util::Color m_intensity;
  util::Tuple m_position;
};

constexpr util::Tuple PointLight::position() const
{
  return m_position;
}
constexpr util::Color PointLight::intensity() const
{
  return m_intensity;
}
constexpr PointLight::PointLight(util::Tuple position, util::Color color) : m_intensity(color), m_position(position)
{
}
}// namespace rt
#endif//MYPROJECT_POINTLIGHT_H

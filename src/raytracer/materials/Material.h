//
// Created by damian on 08.07.2020.
//

#ifndef MYPROJECT_MATERIAL_H
#define MYPROJECT_MATERIAL_H
#include <Color.h>
namespace rt {
class Material
{
public:
  [[nodiscard]] constexpr double ambient() const;
  [[nodiscard]] constexpr double diffuse() const;
  [[nodiscard]] constexpr double specular() const;
  [[nodiscard]] constexpr double shininess() const;
  [[nodiscard]] constexpr util::Color color() const;

private:
  util::Color m_color = util::Color(1, 1, 1);
  double m_ambient = 0.1;
  double m_diffuse = 0.9;
  double m_specular = 0.9;
  double m_shininess = 200.0;
};
constexpr double Material::ambient() const
{
  return m_ambient;
}
constexpr double Material::diffuse() const
{
  return m_diffuse;
}
constexpr double Material::specular() const
{
  return m_specular;
}
constexpr double Material::shininess() const
{
  return m_shininess;
}
constexpr util::Color Material::color() const
{
  return m_color;
}
}
#endif//MYPROJECT_MATERIAL_H

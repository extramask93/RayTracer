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
  constexpr Material &setAmbient(double ambient);
  constexpr Material &setDiffuse(double diffuse);
  constexpr Material &setSpecular(double specular);
  constexpr Material &setShininess(double shininess);
  constexpr Material &setColor(const util::Color &color);
  [[nodiscard]] constexpr double ambient() const;
  [[nodiscard]] constexpr double diffuse() const;
  [[nodiscard]] constexpr double specular() const;
  [[nodiscard]] constexpr double shininess() const;
  [[nodiscard]] constexpr util::Color color() const;
  [[nodiscard]] constexpr bool operator==(const Material &other) const;

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
constexpr bool Material::operator==(const Material &other) const
{
  return (m_ambient == other.m_ambient) && (m_diffuse == other.m_diffuse) && (m_specular == other.m_specular) && (m_shininess == other.m_shininess);
}
constexpr Material &Material::setAmbient(double ambient)
{
  m_ambient = ambient;
  return *this;
}
constexpr Material &Material::setDiffuse(double diffuse)
{
  m_diffuse = diffuse;
  return *this;
}
constexpr Material &Material::setSpecular(double specular)
{
  m_specular = specular;
  return *this;
}
constexpr Material &Material::setShininess(double shininess)
{
  m_shininess = shininess;
  return *this;
}
constexpr Material &Material::setColor(const util::Color &color)
{
  m_color = color;
  return  *this;
}
}// namespace rt
#endif//MYPROJECT_MATERIAL_H

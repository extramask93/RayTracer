//
// Created by damian on 08.07.2020.
//

#ifndef MYPROJECT_MATERIAL_H
#define MYPROJECT_MATERIAL_H
#include <Color.h>
#include <patterns/StripePattern.h>
#include <memory>
namespace rt {
class Material
{
public:
  constexpr Material &setAmbient(double ambient);
  constexpr Material &setDiffuse(double diffuse);
  constexpr Material &setSpecular(double specular);
  constexpr Material &setShininess(double shininess);
  constexpr Material &setColor(const util::Color &color);
  constexpr Material &setReflective(double level);
  constexpr Material &setTransparency(double level);
  constexpr Material &setRefractionIndex(double level);
  Material &setPattern(std::unique_ptr<rt::Pattern> &&pattern);
  [[nodiscard]] constexpr double ambient() const;
  [[nodiscard]] constexpr double diffuse() const;
  [[nodiscard]] constexpr double specular() const;
  [[nodiscard]] constexpr double shininess() const;
  [[nodiscard]] constexpr util::Color color() const;
  [[nodiscard]] constexpr double reflective() const;
  [[nodiscard]] constexpr double transparency() const;
  [[nodiscard]] constexpr double refractionIndex() const;
  [[nodiscard]] rt::Pattern *pattern() const;
  [[nodiscard]] constexpr bool operator==(const Material &other) const;
  /*rule of five */
  Material() = default;
  ~Material() = default;
  Material(Material &&other) noexcept = default;
  Material &operator=(Material &&other) noexcept = default;
  Material(const Material &other)// copy constructor
  {
    /*it may slice https://stackoverflow.com/questions/16030081/copy-constructor-for-a-class-with-unique-ptr*/
    if (other.m_pattern != nullptr) {
      m_pattern = other.m_pattern->clone();
    }
    m_color = other.m_color;
    m_ambient = other.m_ambient;
    m_diffuse = other.m_diffuse;
    m_specular = other.m_specular;
    m_shininess = other.m_shininess;
    m_reflective = other.m_reflective;
    m_refractiveIndex = other.m_refractiveIndex;
    m_transparency = other.m_transparency;
  }
  Material &operator=(const Material &other)// copy assignment
  {
    if (other.m_pattern != nullptr) {
      m_pattern = other.m_pattern->clone();
    }
    m_color = other.m_color;
    m_ambient = other.m_ambient;
    m_diffuse = other.m_diffuse;
    m_specular = other.m_specular;
    m_shininess = other.m_shininess;
    m_reflective = other.m_reflective;
    m_refractiveIndex = other.m_refractiveIndex;
    m_transparency = other.m_transparency;
    return *this;
  }


private:
  util::Color m_color = util::Color(1, 1, 1);
  double m_ambient = 0.1;
  double m_diffuse = 0.9;
  double m_specular = 0.9;
  double m_shininess = 200.0;
  double m_reflective = 0.0;
  double m_transparency = 0.0;
  double m_refractiveIndex = 1.0;
  std::unique_ptr<rt::Pattern> m_pattern;
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
  return *this;
}
constexpr Material &Material::setReflective(double level)
{
  m_reflective = level;
  return *this;

}
constexpr double Material::reflective() const
{
  return m_reflective;
}
constexpr double Material::transparency() const
{
  return m_transparency;
}
constexpr double Material::refractionIndex() const
{
  return m_refractiveIndex;
}
constexpr Material &Material::setTransparency(double level)
{
  m_transparency = level;
  return *this;
}
constexpr Material &Material::setRefractionIndex(double level)
{
  m_refractiveIndex = level;
  return *this;
}


}// namespace rt
#endif//MYPROJECT_MATERIAL_H

//
// Created by damian on 08.07.2020.
//

#include "Material.h"
namespace rt {

Material &Material::setPattern(std::unique_ptr<rt::Pattern>&& pattern)
{
  m_pattern = std::move(pattern);
  return *this;
}
rt::Pattern* Material::pattern() const
{
  return m_pattern.get();
}
}

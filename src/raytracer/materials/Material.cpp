//
// Created by damian on 08.07.2020.
//

#include "Material.h"
namespace rt {

Material &Material::setPattern(std::unique_ptr<rt::StripePattern>&& pattern)
{
  m_pattern = std::move(pattern);
  return *this;
}
rt::StripePattern* Material::pattern() const
{
  return m_pattern.get();
}
}

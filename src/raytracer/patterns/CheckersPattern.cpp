//
// Created by damian on 15.07.2020.
//

#include "CheckersPattern.h"
util::Color rt::CheckersPattern::patternAt(const util::Tuple &point) const
{
  //TODO UV mapping, spherical texture mapping
  auto sum = std::abs(point.x()) + std::abs(point.y()) + std::abs(point.z());
  if(static_cast<int>(sum) % 2) {
    return m_b;
  }
  return m_a;
}
rt::Pattern *rt::CheckersPattern::clone_impl() const
{
  return new CheckersPattern(*this);
}
rt::CheckersPattern::CheckersPattern(const util::Color &a, const util::Color &b) : Pattern(a, b)
{
}

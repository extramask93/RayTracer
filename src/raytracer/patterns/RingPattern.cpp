//
// Created by damian on 15.07.2020.
//

#include "RingPattern.h"
#include <cmath>
util::Color rt::RingPattern::patternAt(const util::Tuple &point) const
{
  if(static_cast<int>(std::floor(std::sqrt(std::pow(point.x(),2) + std::pow(point.z(),2)))) % 2) {
    return m_b;
  }
  return m_a;
}
rt::Pattern *rt::RingPattern::clone_impl() const
{
  return new RingPattern(*this);
}
rt::RingPattern::RingPattern(const util::Color &a, const util::Color &b) : Pattern(a, b)
{
}

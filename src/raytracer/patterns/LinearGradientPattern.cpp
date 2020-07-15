//
// Created by damian on 15.07.2020.
//

#include "LinearGradientPattern.h"
#include <cmath>

util::Color rt::LinearGradientPattern::patternAt(const util::Tuple &point) const
{
  auto distance = m_b-m_a;
  auto fraction = point.x() - std::floor(point.x());
  return m_a + distance * fraction;
}
rt::Pattern *rt::LinearGradientPattern::clone_impl() const
{
  return new LinearGradientPattern(*this);
}
rt::LinearGradientPattern::LinearGradientPattern(const util::Color &a, const util::Color &b) : Pattern(a,b)
{
}

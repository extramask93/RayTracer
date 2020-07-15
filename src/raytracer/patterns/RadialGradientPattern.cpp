//
// Created by damian on 15.07.2020.
//

#include "RadialGradientPattern.h"
#include <cmath>
util::Color rt::RadialGradientPattern::patternAt(const util::Tuple &point) const
{

  auto distanceColor = m_b-m_a;
  auto distancePoint = std::sqrt(std::pow(point.x(),2) + std::pow(point.z(),2));
  auto fraction = distancePoint - std::floor(distancePoint);
  return m_a + distanceColor * fraction;

}
rt::Pattern *rt::RadialGradientPattern::clone_impl() const
{
  return new RadialGradientPattern(*this);
}
rt::RadialGradientPattern::RadialGradientPattern(const util::Color &a, const util::Color &b) : Pattern(a, b)
{
}

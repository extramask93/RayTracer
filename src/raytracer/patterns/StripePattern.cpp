//
// Created by damian on 13.07.2020.
//

#include "StripePattern.h"
#include <cmath>
rt::StripePattern::StripePattern(const util::Color &a, const util::Color &b) : Pattern(a, b)
{
}
util::Color rt::StripePattern::patternAt(const util::Tuple &point) const
{
  if (static_cast<int>(std::floor(point.x())) % 2) {
    return b();
  } else {
    return a();
  }
}
rt::Pattern *rt::StripePattern::clone_impl() const
{
 return new StripePattern(*this);
}

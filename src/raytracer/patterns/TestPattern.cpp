//
// Created by damian on 17.07.2020.
//

#include "TestPattern.h"
util::Color rt::TestPattern::patternAt(const util::Tuple &point) const
{
  return util::Color(point.x(), point.y(), point.z());
}
rt::Pattern *rt::TestPattern::clone_impl() const
{
  return new TestPattern(*this);
}
rt::TestPattern::TestPattern(const util::Color &a, const util::Color &b) : Pattern(a, b)
{
}

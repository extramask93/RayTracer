//
// Created by damian on 03.08.2020.
//

#include "UVCheckers.h"
util::Color rt::UVCheckers::patternAt(const util::Tuple &point) const
{
  auto u = point.x();
  auto v = point.y();
  auto u2 = static_cast<unsigned>(floor(u * m_width));
  auto v2 = static_cast<unsigned>(floor(v * m_height));
  if((u2+v2) % 2 == 0) {
    return m_a;
  } else {
    return m_b;
  }
}
rt::Pattern *rt::UVCheckers::clone_impl() const
{
  return new UVCheckers(*this);
}
rt::UVCheckers::UVCheckers(unsigned int width, unsigned int height, const util::Color &a, const util::Color &b)
:  Pattern(a,b), m_width(width), m_height(height)
{
}
util::Color rt::UVCheckers::uvPatternAt(double u, double v) const
{
  auto u2 = static_cast<unsigned>(floor(u * m_width));
  auto v2 = static_cast<unsigned>(floor(v * m_height));
  if((u2+v2) % 2 == 0) {
    return m_a;
  } else {
    return m_b;
  }
}

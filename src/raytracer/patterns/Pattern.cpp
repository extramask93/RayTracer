//
// Created by damian on 14.07.2020.
//

#include "Pattern.h"
namespace rt {
Pattern::Pattern(const util::Color &a, const util::Color &b) : m_a(a), m_b(b),
                                                                   m_transform(util::Matrixd::Identity(4))
{
}

util::Color Pattern::b() const
{
  return  m_b;
}
util::Color Pattern::a() const
{
  return m_a;
}
const util::Matrixd& Pattern::transform() const
{
  return m_transform;
}
util::Matrixd& Pattern::transform()
{
  return m_transform;
}
util::Color Pattern::uvPatternAt(double u, double v) const
{
  (void)u;
  (void)v;
  return util::Color(0, 0, 0);
}

}// namespace rt
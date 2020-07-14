//
// Created by damian on 13.07.2020.
//

#include "StripePattern.h"
rt::StripePattern::StripePattern(const util::Color &a, const util::Color &b): m_a(a), m_b(b),
                                                                               m_transform(util::Matrixd::Identity(4))
{
}
util::Color rt::StripePattern::b() const
{
  return  m_b;
}
util::Color rt::StripePattern::a() const
{
  return m_a;
}
const util::Matrixd& rt::StripePattern::transform() const
{
  return m_transform;
}
 util::Matrixd& rt::StripePattern::transform()
{
  return m_transform;
}
void rt::StripePattern::setTransform(const util::Matrixd &transform)
{
  m_transform = transform;
}

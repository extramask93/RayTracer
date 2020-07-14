//
// Created by damian on 13.07.2020.
//

#include "StripePattern.h"
rt::StripePattern::StripePattern(const util::Color &a, const util::Color &b): m_a(a), m_b(b)
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

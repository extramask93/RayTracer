//
// Created by damian on 13.07.2020.
//

#ifndef MYPROJECT_STRIPEPATTERN_H
#define MYPROJECT_STRIPEPATTERN_H
#include <Color.h>
namespace rt {
class StripePattern
{
public:
  explicit StripePattern(const util::Color &a, const util::Color &b);
  [[nodiscard]] util::Color a() const;
  [[nodiscard]] util::Color b() const;
private:
  util::Color m_a;
  util::Color m_b;
};
}


#endif//MYPROJECT_STRIPEPATTERN_H

//
// Created by damian on 13.07.2020.
//

#ifndef MYPROJECT_STRIPEPATTERN_H
#define MYPROJECT_STRIPEPATTERN_H
#include <Color.h>
#include <Matrix.h>
#include "Pattern.h"
namespace rt {
class StripePattern : public Pattern
{
public:
  explicit StripePattern(const util::Color &a, const util::Color &b);
  util::Color patternAt(const util::Tuple &point) const override;

protected:
  Pattern *clone_impl() const override;
};
}


#endif//MYPROJECT_STRIPEPATTERN_H

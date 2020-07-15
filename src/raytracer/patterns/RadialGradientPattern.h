//
// Created by damian on 15.07.2020.
//

#ifndef MYPROJECT_RADIALGRADIENTPATTERN_H
#define MYPROJECT_RADIALGRADIENTPATTERN_H
#include "Pattern.h"
namespace rt {
class RadialGradientPattern : public Pattern
{
public:
  explicit RadialGradientPattern(const util::Color &a, const util::Color &b);
  util::Color patternAt(const util::Tuple &point) const override;
protected:
  Pattern *clone_impl() const override;
};
}


#endif//MYPROJECT_RADIALGRADIENTPATTERN_H

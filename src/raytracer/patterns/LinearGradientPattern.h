//
// Created by damian on 15.07.2020.
//

#ifndef MYPROJECT_LINEARGRADIENTPATTERN_H
#define MYPROJECT_LINEARGRADIENTPATTERN_H

#include "Pattern.h"
namespace rt {
class LinearGradientPattern : public Pattern
{
public:
  explicit LinearGradientPattern(const util::Color &a, const util::Color &b);
  util::Color patternAt(const util::Tuple &point) const override;

protected:
  Pattern *clone_impl() const override;
};
}


#endif//MYPROJECT_LINEARGRADIENTPATTERN_H

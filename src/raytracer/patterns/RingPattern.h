//
// Created by damian on 15.07.2020.
//

#ifndef MYPROJECT_RINGPATTERN_H
#define MYPROJECT_RINGPATTERN_H
#include "Pattern.h"
namespace rt {
class RingPattern : public Pattern
{
public:
  explicit RingPattern(const util::Color &a, const util::Color &b);
  util::Color patternAt(const util::Tuple &point) const override;
protected:
  Pattern *clone_impl() const override;
};
}


#endif//MYPROJECT_RINGPATTERN_H

//
// Created by damian on 15.07.2020.
//

#ifndef MYPROJECT_CHECKERSPATTERN_H
#define MYPROJECT_CHECKERSPATTERN_H
#include "Pattern.h"
namespace rt {
class CheckersPattern : public Pattern

{
public:
  explicit CheckersPattern(const util::Color &a, const util::Color &b);
  util::Color patternAt(const util::Tuple &point) const override;
protected:
  Pattern *clone_impl() const override;
};
}


#endif//MYPROJECT_CHECKERSPATTERN_H

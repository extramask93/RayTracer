//
// Created by damian on 17.07.2020.
//

#ifndef MYPROJECT_TESTPATTERN_H
#define MYPROJECT_TESTPATTERN_H
#include <patterns/Pattern.h>
namespace rt {
class TestPattern : public Pattern
{
public:
  explicit TestPattern(const util::Color &a, const util::Color &b);
  util::Color patternAt(const util::Tuple &point) const override;
protected:
  Pattern *clone_impl() const override;
};

}


#endif//MYPROJECT_TESTPATTERN_H

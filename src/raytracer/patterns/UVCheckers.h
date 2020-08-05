//
// Created by damian on 03.08.2020.
//

#ifndef MYPROJECT_UVCHECKERS_H
#define MYPROJECT_UVCHECKERS_H
#include <patterns/Pattern.h>
namespace rt {
class UVCheckers : public Pattern
{
public:
  UVCheckers(unsigned width, unsigned height, const util::Color &a, const util::Color &b);
public:
  util::Color uvPatternAt(double u, double v) const override;
  util::Color patternAt(const util::Tuple &point) const override;
protected:
  Pattern *clone_impl() const override;

protected:
  double m_v;
  double m_u;
  unsigned m_width;
  unsigned m_height;
};
}


#endif//MYPROJECT_UVCHECKERS_H

//
// Created by damian on 13.07.2020.
//

#ifndef MYPROJECT_STRIPEPATTERN_H
#define MYPROJECT_STRIPEPATTERN_H
#include <Color.h>
#include <Matrix.h>
namespace rt {
class StripePattern
{
public:
  explicit StripePattern(const util::Color &a, const util::Color &b);
  [[nodiscard]] util::Color a() const;
  [[nodiscard]] util::Color b() const;
  [[nodiscard]] const util::Matrixd& transform() const;
  [[nodiscard]] util::Matrixd& transform() ;
  void setTransform(const util::Matrixd &transform) ;
private:
  util::Color m_a;
  util::Color m_b;
  util::Matrixd m_transform;
};
}


#endif//MYPROJECT_STRIPEPATTERN_H

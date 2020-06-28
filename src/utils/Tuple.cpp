//
// Created by damian on 23.05.2020.
//

#include "Tuple.h"
namespace util {
std::ostream &operator<<(std::ostream &o, const util::Tuple &t)
{
  o << '(' << t.x() << ',' << t.y() << ',' << t.z() << ',' << t.w() << ')';
  return o;
}
TupleType Tuple::magnitude() const
{
  if(isPoint()) {
    return 0.0;
  }
  return std::sqrt(std::pow(x(),2) + std::pow(y(),2) + std::pow(z(),2) + std::pow(w(),2));
}
Tuple &Tuple::normalize()
{
  auto magnitude = Tuple::magnitude();
  x() = x() / magnitude;
  y()= y() / magnitude;
  z() = z() / magnitude;
  w() = w() / magnitude;
  return *this;
}

}

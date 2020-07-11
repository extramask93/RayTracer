//
// Created by damian on 29.05.2020.
//

#include "Color.h"
namespace util {
const util::Color Color::BLACK = util::Color(0, 0, 0);
std::ostream &operator<<(std::ostream &o, const util::Color &c)
{
  o << '(' << c.r << ',' << c.g << ',' << c.b << ')';
  return o;
}
}// namespace util

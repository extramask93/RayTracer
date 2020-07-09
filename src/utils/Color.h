//
// Created by damian on 29.05.2020.
//

#ifndef MYPROJECT_COLOR_H
#define MYPROJECT_COLOR_H
#include "Tuple.h"

namespace util {
class Color
{
public:

  explicit constexpr Color(TupleType red, TupleType green, TupleType blue) : r(red), g(green), b(blue) {}
  constexpr Color operator+(const Color &other) const
  {
    return Color(r + other.r, g + other.g, b + other.b);
  }
  constexpr Color operator-(const Color &other) const
  {
    return Color(r - other.r, g - other.g, b - other.b);
  }
  constexpr Color operator*(const Color &other) const
  {
    return Color(r * other.r, g * other.g, b * other.b);
  }
  constexpr Color operator*(const TupleType c) const
  {
    return Color(r * c, g * c, b * c);
  }
  bool operator==(const Color &c) const
  {
    return Color::equal(r, c.r) && equal(g, c.g) && equal(b,c.b) ;
  }
private:
  static bool equal(TupleType lhs, TupleType rhs)
  {
    auto difference = std::abs(lhs - rhs);
    return difference <= eps_;
  }
  static constexpr TupleType eps_ = 0.00001;
public:
  TupleType r;
  TupleType g;
  TupleType b;
  static const util::Color BLACK;
};
}// namespace util


#endif//MYPROJECT_COLOR_H

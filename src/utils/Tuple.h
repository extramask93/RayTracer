// Created by damian on 23.05.2020.
//

#ifndef MYPROJECT_TUPLE_H
#define MYPROJECT_TUPLE_H
#include <cmath>
namespace util {
using TupleType = double;
class Tuple
{
public:
  constexpr Tuple(TupleType x_, TupleType y_, TupleType z_, TupleType w_) : x(x_), y(y_), z(z_), w(w_) {}
  static constexpr Tuple point(TupleType x_, TupleType y_, TupleType z_)
  {
    return Tuple(x_, y_, z_, 1.0);
  }
  static constexpr Tuple vector(TupleType x_, TupleType y_, TupleType z_)
  {
    return Tuple(x_, y_, z_, 0.0);
  }
  constexpr bool operator==(const Tuple &other) const
  {
    return equal(x , other.x) && equal(y, other.y) && equal(z, other.z) && equal(w , other.w);
  }
  constexpr Tuple operator+(const Tuple &other) const {
    return Tuple(x+other.x, y+other.y, z+other.z, 1.0);
  }
  constexpr Tuple operator-(const Tuple &other) const {
    if((other.isVector() && isPoint()) || (other.isPoint() && isVector())) {
      return Tuple::point(x-other.x, y-other.y, z-other.z);
    }
    return Tuple::vector(x-other.x, y-other.y, z-other.z);
  }
  constexpr bool isPoint() const { return w == 1.0; }
  constexpr bool isVector() const { return !isPoint(); }
  TupleType x;
  TupleType y;
  TupleType z;
  TupleType w;

private:
  static constexpr bool equal(TupleType lhs, TupleType rhs) {
    auto difference = std::abs(lhs-rhs);
    return difference > eps_ ? false : true;
  }
private:
  static constexpr TupleType eps_ = 0.00001;
};
}// namespace util

#endif//MYPROJECT_TUPLE_H

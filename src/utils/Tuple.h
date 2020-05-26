// Created by damian on 23.05.2020.
//

#ifndef MYPROJECT_TUPLE_H
#define MYPROJECT_TUPLE_H
#include <cmath>
#include <ostream>
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
  bool operator==(const Tuple &other) const
  {
    return Tuple::equal(x, other.x) && equal(y, other.y) && equal(z, other.z) && equal(w, other.w);
  }
  constexpr Tuple operator+(const Tuple &other) const
  {
    return Tuple(x + other.x, y + other.y, z + other.z, 1.0);
  }
  constexpr Tuple operator*(const double scalar) const
  {
    auto result = Tuple(x * scalar, y * scalar, z * scalar, w * scalar);
    return result;
  }
  constexpr Tuple operator/(const double scalar) const
  {
    auto result = Tuple(x / scalar, y / scalar, z / scalar, w / scalar);
    return result;
  }
  constexpr Tuple operator-(const Tuple &other) const
  {
    if ((other.isVector() && isPoint()) || (other.isPoint() && isVector())) {
      return Tuple(x - other.x, y - other.y, z - other.z, other.w > w ? other.w : w);
    }
    return Tuple::vector(x - other.x, y - other.y, z - other.z);
  }
  constexpr Tuple operator-() const
  {
    return util::Tuple(0, 0, 0, -this->w) - *this;
  }
  Tuple &normalize();
  [[nodiscard]] TupleType magnitude() const;
  [[nodiscard]] constexpr TupleType dot(const Tuple &other) const { return x * other.x + y * other.y + z * other.z + w * other.w; }
  [[nodiscard]] constexpr Tuple cross(const Tuple &other) const
  {
    return Tuple::vector(y * other.z - z * other.y, z * other.x - x * other.z, x * other.y - y * other.x);
  };
  [[nodiscard]] constexpr bool isPoint() const { return w > 0.0; }
  [[nodiscard]] constexpr bool isVector() const { return !isPoint(); }
  friend std::ostream &operator<<(std::ostream &o, const Tuple &t);
  TupleType x;
  TupleType y;
  TupleType z;
  TupleType w;

private:
  static bool equal(TupleType lhs, TupleType rhs)
  {
    auto difference = std::abs(lhs - rhs);
    return difference <= eps_;
  }
  static constexpr TupleType eps_ = 0.00001;
};
}// namespace util

#endif//MYPROJECT_TUPLE_H

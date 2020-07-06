// Created by()damian on 23.05.2020.
//

#ifndef MYPROJECT_TUPLE_H
#define MYPROJECT_TUPLE_H
#include <cmath>
#include <ostream>
#include <array>
namespace util {
using TupleType = double;
class Tuple
{
public:
  constexpr Tuple(TupleType x_, TupleType y_, TupleType z_, TupleType w_)  {
    data[0] =x_;
    data[1] = y_;
    data[2] = z_;
    data[3] = w_;
  }

  [[nodiscard]] constexpr TupleType& x() {return data[0];}
  [[nodiscard]] constexpr TupleType& y() {return data[1];}
  [[nodiscard]] constexpr TupleType& z() {return data[2];}
  [[nodiscard]] constexpr TupleType& w() {return data[3];}
  [[nodiscard]] constexpr TupleType x() const {return data[0];}
  [[nodiscard]] constexpr TupleType y() const {return data[1];}
  [[nodiscard]] constexpr TupleType z() const {return data[2];}
  [[nodiscard]] constexpr TupleType w() const {return data[3];}
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
    return Tuple::equal(x(), other.x()) && equal(y(), other.y()) && equal(z(), other.z()) && equal(w(), other.w());
  }
  constexpr Tuple operator+(const Tuple &other) const
  {
    return Tuple(x()+ other.x(), y()+ other.y(), z()+ other.z(), 1.0);
  }
  constexpr Tuple operator*(const double scalar) const
  {
    auto result = Tuple(x()* scalar, y()* scalar, z()* scalar, w()* scalar);
    return result;
  }
  constexpr Tuple operator/(const double scalar) const
  {
    auto result = Tuple(x()/ scalar, y()/ scalar, z()/ scalar, w()/ scalar);
    return result;
  }
  constexpr Tuple operator-(const Tuple &other) const
  {
    if ((other.isVector() && isPoint()) || (other.isPoint() && isVector())) {
      return Tuple(x()- other.x(), y()- other.y(), z()- other.z(), other.w()> w()? other.w(): w());
    }
    return Tuple::vector(x()- other.x(), y()- other.y(), z()- other.z());
  }
  constexpr Tuple operator-() const
  {
    return util::Tuple(0, 0, 0, -w()) - *this;
  }
  constexpr TupleType operator()(unsigned row, unsigned column) const {
    (void)column;
    return data[row];
  }
  constexpr TupleType& operator()(unsigned row, unsigned column) {
    (void)column;
    return data[row];
  }
  Tuple &normalize();
  [[nodiscard]] TupleType magnitude() const;
  [[nodiscard]] constexpr TupleType dot(const Tuple &other) const { return x()* other.x()+ y()* other.y()+ z()* other.z()+ w()* other.w(); }
  [[nodiscard]] constexpr Tuple cross(const Tuple &other) const
  {
    return Tuple::vector(y()* other.z()- z()* other.y(), z()* other.x()- x()* other.z(), x()* other.y()- y()* other.x());
  };
  [[nodiscard]] constexpr bool isPoint() const { return w()> 0.0; }
  [[nodiscard]] constexpr bool isVector() const { return !isPoint(); }
  friend std::ostream &operator<<(std::ostream &o, const Tuple &t);
  std::array<TupleType,4> data{0,0,0,0};

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

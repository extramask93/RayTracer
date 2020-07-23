//
// Created by damian on 23.07.2020.
//

#ifndef MYPROJECT_MATH_H
#define MYPROJECT_MATH_H
#include <limits>
#include <numbers>

namespace math {

template<typename T = double>
constexpr T pi = std::numbers::pi_v<T>;
template<typename T = double>
constexpr T inf = std::numeric_limits<T>::infinity();
template<typename T = double>
constexpr T ninf = -std::numeric_limits<T>::infinity();

constexpr double absd(const double d)
{
  return d >= 0 ? d : -d;
}
}// namespace math
#endif//MYPROJECT_MATH_H

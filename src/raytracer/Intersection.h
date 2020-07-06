//
// Created by damian on 06.07.2020.
//

#ifndef MYPROJECT_INTERSECTION_H
#define MYPROJECT_INTERSECTION_H


#include <initializer_list>
#include <vector>
#include <algorithm>
namespace rt {
class Intersection
{
public:
  explicit Intersection(std::initializer_list<double> ticks);
  [[nodiscard]] std::size_t count() const;
  [[nodiscard]] constexpr double t() const;
  [[nodiscard]] double operator[](unsigned index) const;

private:
  double m_t;
  std::vector<double> m_ticks;
};
std::vector<Intersection> Intersections(std::initializer_list<Intersection> intersections);
constexpr double Intersection::t() const
{
  return m_t;
}
}


#endif//MYPROJECT_INTERSECTION_H

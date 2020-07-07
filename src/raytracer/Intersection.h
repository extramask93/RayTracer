//
// Created by damian on 06.07.2020.
//

#ifndef MYPROJECT_INTERSECTION_H
#define MYPROJECT_INTERSECTION_H


#include <initializer_list>
#include <vector>
#include <algorithm>
#include <shapes/Shape.h>
namespace rt {

class Intersection
{
public:
  Intersection(double t, const rt::Shape &shape);
  [[nodiscard]] constexpr double t() const;
  [[nodiscard]] constexpr const rt::Shape& object() const;
private:
  const rt::Shape &m_shape;
  double m_t;
};

class Intersections : public std::vector<Intersection> {
  using std::vector<Intersection>::vector;
  /*currently no need for implementation*/
};
constexpr const rt::Shape &Intersection::object() const
{
  return m_shape;
}
constexpr double Intersection::t() const
{
  return m_t;
}

}


#endif//MYPROJECT_INTERSECTION_H

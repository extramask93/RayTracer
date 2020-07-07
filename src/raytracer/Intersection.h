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
  Intersection(double t, const Shape * shape);
  bool operator==(const Intersection &other) const;
  bool operator<(const Intersection &other) const;
  [[nodiscard]] constexpr double t() const;
  [[nodiscard]] constexpr const rt::Shape*  object() const;
private:
  const Shape * m_shape;
  double m_t;
};

class Intersections : public std::vector<Intersection> {
 // using std::vector<Intersection>::vector;

public:
  std::optional<Intersection> hit();
  explicit Intersections(const std::initializer_list<Intersection> &elems);
};
constexpr const rt::Shape* Intersection::object() const
{
  return m_shape;
}
constexpr double Intersection::t() const
{
  return m_t;
}



}


#endif//MYPROJECT_INTERSECTION_H

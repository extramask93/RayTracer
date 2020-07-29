//
// Created by damian on 06.07.2020.
//

#ifndef MYPROJECT_INTERSECTION_H
#define MYPROJECT_INTERSECTION_H


#include <initializer_list>
#include <vector>
#include <algorithm>
#include <optional>
namespace rt {
class Shape;
class Intersection
{
public:
  Intersection(double t, const Shape * shape, double u = 0.0, double v = 0.0);
  [[nodiscard]]  bool operator==(const Intersection &other) const;
  [[nodiscard]]  bool operator<(const Intersection &other) const;
  [[nodiscard]]  double t() const;
  [[nodiscard]]  double u() const;
  [[nodiscard]]  double v() const;
  [[nodiscard]]  const rt::Shape*  object() const;
private:
  const Shape * m_shape;
  double m_t;
  double m_u;
  double m_v;
};



}


#endif//MYPROJECT_INTERSECTION_H

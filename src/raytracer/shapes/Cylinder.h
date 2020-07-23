//
// Created by damian on 21.07.2020.
//

#ifndef MYPROJECT_CYLINDER_H
#define MYPROJECT_CYLINDER_H
#include <shapes/Shape.h>
namespace rt {

class Cylinder : public Shape
{
public:
  Intersections localIntersect(const Ray &ray) const override;
  util::Tuple localNormalAt(const util::Tuple &point) const override;
  double &minimum();
  const double &minimum() const;
  double &maximum();
  const double &maximum() const;
  bool &closed();
  const bool &closed() const;
  AABB bounds() const override;

protected:
  bool checkCap(const rt::Ray &ray, double t) const;
  void intersectCaps(const rt::Ray &ray, Intersections &intersections) const;
protected:
  double m_min = math::ninf<>;
  double m_max = math::inf<>;
  bool m_closed = false;
};

}// namespace rt


#endif//MYPROJECT_CYLINDER_H

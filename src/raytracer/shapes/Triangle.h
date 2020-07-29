//
// Created by damian on 25.07.2020.
//

#ifndef MYPROJECT_TRIANGLE_H
#define MYPROJECT_TRIANGLE_H

#include <shapes/Shape.h>
namespace rt {
class Triangle : public Shape
{
public:
  explicit Triangle(const util::Tuple &p1, const util::Tuple &p2, const util::Tuple &p3);
  const util::Tuple& p1() const;
  const util::Tuple& p2() const;
  const util::Tuple& p3() const;
  const util::Tuple& e1() const;
  const util::Tuple& e2() const;
  const util::Tuple& normal() const;
  AABB bounds() const override;
  Intersections localIntersect(const Ray &ray) const override;
  util::Tuple localNormalAt(const util::Tuple &point, const rt::Intersection &intersection) const override;

protected:
  util::Tuple m_p1;
  util::Tuple m_p2;
  util::Tuple m_p3;
  util::Tuple m_e1;
  util::Tuple m_e2;
  util::Tuple m_normal;
};
}


#endif//MYPROJECT_TRIANGLE_H

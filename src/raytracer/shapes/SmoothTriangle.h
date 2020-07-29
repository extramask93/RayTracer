//
// Created by damian on 28.07.2020.
//

#ifndef MYPROJECT_SMOOTHTRIANGLE_H
#define MYPROJECT_SMOOTHTRIANGLE_H

#include <shapes/Triangle.h>
namespace rt {
class SmoothTriangle : public Triangle
{
public:
  SmoothTriangle(const util::Tuple &p1,const util::Tuple &p2,const util::Tuple &p3,
                 const util::Tuple &n1,const util::Tuple &n2,const util::Tuple &n3);
  const util::Tuple& n1() const;
  const util::Tuple& n2() const;
  const util::Tuple& n3() const;
  Intersections localIntersect(const Ray &ray) const override;
  util::Tuple localNormalAt(const util::Tuple &point, const Intersection &intersection) const override;

protected:
  util::Tuple m_n1;
  util::Tuple m_n2;
  util::Tuple m_n3;
};
}// namespace rt


#endif//MYPROJECT_SMOOTHTRIANGLE_H

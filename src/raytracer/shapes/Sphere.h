//
// Created by damian on 06.07.2020.
//

#ifndef MYPROJECT_SPHERE_H
#define MYPROJECT_SPHERE_H
#include <shapes/Shape.h>
#include <intersections/Intersections.h>
namespace rt {
class Sphere : public Shape
{
public:
  explicit Sphere();
  Intersections intersect(Ray ray)const override;
  util::Matrixd transform() const;
  void setTransform(const util::Matrixd &transform);
  util::Tuple normalAt(util::Tuple point)const override;

private:
  util::Matrixd m_transform;
  util::Tuple m_origin;
};
}


#endif//MYPROJECT_SPHERE_H

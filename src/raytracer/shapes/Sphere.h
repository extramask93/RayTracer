//
// Created by damian on 06.07.2020.
//

#ifndef MYPROJECT_SPHERE_H
#define MYPROJECT_SPHERE_H
#include <shapes/Shape.h>
namespace rt {
class Sphere : public Shape
{
public:
  explicit Sphere();
  Intersections intersect(Ray ray) override;
  util::Matrixd transform() const;
  void setTransform(const util::Matrixd &transform);
  util::Tuple normalAt(util::Tuple point) override;

private:
  util::Matrixd m_transform;
  util::Tuple m_origin;
};
}


#endif//MYPROJECT_SPHERE_H

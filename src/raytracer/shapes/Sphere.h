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
  Intersections localIntersect(const Ray &ray)const override;
  util::Tuple localNormalAt(const util::Tuple &point)const override;
  static Sphere glassSphere();
private:
};
}


#endif//MYPROJECT_SPHERE_H

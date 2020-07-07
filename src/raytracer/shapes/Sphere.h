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
};
}


#endif//MYPROJECT_SPHERE_H

//
// Created by damian on 21.07.2020.
//

#ifndef MYPROJECT_CONE_H
#define MYPROJECT_CONE_H
#include <shapes/Cylinder.h>
namespace rt {
class Cone : public Cylinder
{
public:
  Intersections localIntersect(const Ray &ray) const override;
  util::Tuple localNormalAt(const util::Tuple &point) const override;
};
}


#endif//MYPROJECT_CONE_H

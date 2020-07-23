//
// Created by damian on 20.07.2020.
//

#ifndef MYPROJECT_CUBE_H
#define MYPROJECT_CUBE_H
#include <shapes/Shape.h>
namespace rt {
class Cube : public Shape
{
public:
  Intersections localIntersect(const Ray &ray) const override;
  util::Tuple localNormalAt(const util::Tuple &point) const override;
  AABB bounds() const override;

private:
  std::pair<double,double> checkAxis(double origin,double direction) const;
};
}


#endif//MYPROJECT_CUBE_H

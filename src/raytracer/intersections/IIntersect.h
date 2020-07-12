//
// Created by damian on 09.07.2020.
//

#ifndef MYPROJECT_IINTERSECT_H
#define MYPROJECT_IINTERSECT_H
#include <ray/Ray.h>
namespace rt {
class Intersections;
class IIntersect
{
public:
  virtual Intersections intersect(const Ray &ray) const = 0;
  virtual ~IIntersect() = default;
  IIntersect() = default;
  IIntersect(const IIntersect &copyFrom) = default;
  IIntersect(IIntersect &&moveFrom) = default;
  IIntersect& operator=(const IIntersect &assignFrom) = default;
  IIntersect& operator=(IIntersect &&moveFrom) = default;
};
}


#endif//MYPROJECT_IINTERSECT_H

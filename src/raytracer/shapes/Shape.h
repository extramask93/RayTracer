//
// Created by damian on 06.07.2020.
//

#ifndef MYPROJECT_SHAPE_H
#define MYPROJECT_SHAPE_H

#include <ray/Ray.h>
namespace rt {
class Intersections;
class Shape
{
public:
  explicit Shape();
  virtual Intersections intersect(Ray ray) =0;
  virtual bool operator==(const Shape &other) const final;
  virtual ~Shape() = default;
  Shape(const Shape &copyFrom) = default;
  Shape(Shape &&moveFrom) = default;
  Shape& operator=(const Shape &assignFrom) = default;
  Shape& operator=(Shape &&moveFrom) = default;

protected:
  unsigned m_id;
  static unsigned m_objCounter;
};

}


#endif//MYPROJECT_SHAPE_H

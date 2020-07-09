//
// Created by damian on 06.07.2020.
//

#ifndef MYPROJECT_SHAPE_H
#define MYPROJECT_SHAPE_H

#include <ray/Ray.h>
#include <materials/Material.h>
namespace rt {
class Intersections;
class Shape
{
public:
  explicit Shape();
  virtual Intersections intersect(Ray ray)const =0;
  virtual util::Tuple normalAt(util::Tuple point) const = 0;
  virtual rt::Material material() const;
  virtual void setMaterial(const rt::Material &mat);
  virtual bool operator==(const Shape &other) const final;
  virtual ~Shape() = default;
  Shape(const Shape &copyFrom) = default;
  Shape(Shape &&moveFrom) = default;
  Shape& operator=(const Shape &assignFrom) = default;
  Shape& operator=(Shape &&moveFrom) = default;

protected:
  unsigned m_id;
  rt::Material m_material;
  static unsigned m_objCounter;
};

}


#endif//MYPROJECT_SHAPE_H

//
// Created by damian on 06.07.2020.
//

#ifndef MYPROJECT_SHAPE_H
#define MYPROJECT_SHAPE_H

#include <ray/Ray.h>
#include <materials/Material.h>
#include <intersections/IIntersect.h>
namespace rt {
class Intersection;
class Intersections;
class Shape : public IIntersect
{
public:
  explicit Shape();
  virtual Intersections intersect(const Ray &ray) const override final;
  virtual util::Tuple normalAt(const util::Tuple &point) const final;
  virtual void setTransform(const util::Matrixd &transform);
  virtual const util::Matrixd& transform() const;
  virtual util::Matrixd& transform() ;
  virtual const rt::Material& material() const;
  virtual rt::Material& material() ;
  virtual void setMaterial(const rt::Material &mat);
  virtual bool operator==(const Shape &other) const final;
  virtual ~Shape() = default;
  Shape(const Shape &copyFrom) = default;
  Shape(Shape &&moveFrom) = default;
  Shape& operator=(const Shape &assignFrom) = default;
  Shape& operator=(Shape &&moveFrom) = default;
  virtual Intersections localIntersect(const Ray &ray) const = 0;
  virtual util::Tuple localNormalAt(const util::Tuple &point) const = 0;
protected:
  unsigned m_id;
  rt::Material m_material;
  util::Matrixd m_transform;
  static unsigned m_objCounter;
  util::Tuple m_origin;
};

}


#endif//MYPROJECT_SHAPE_H

//
// Created by damian on 06.07.2020.
//

#ifndef MYPROJECT_SHAPE_H
#define MYPROJECT_SHAPE_H

#include <ray/Ray.h>
#include <misc/AABB.h>
#include <materials/Material.h>
#include <intersections/IIntersect.h>
#include <intersections/Intersection.h>
namespace rt {
class Intersection;
class Intersections;
class Shape : public IIntersect
{
public:
  explicit Shape();
  virtual Intersections intersect(const Ray &ray) const override final;
  virtual util::Tuple normalAt(const util::Tuple &point, const rt::Intersection &interserction = rt::Intersection(0, nullptr)) const final;
  virtual void setTransform(const util::Matrixd &transform);
  virtual const util::Matrixd& transform() const;
  virtual util::Matrixd& transform() ;
  virtual const rt::Material& material() const;
  virtual rt::Material& material() ;
  virtual void setMaterial(const rt::Material &mat);
  virtual const std::shared_ptr<const Shape> parent() const;
  virtual void setParent(const std::shared_ptr<Shape> &parent);
  virtual bool operator==(const Shape &other) const final;
  virtual util::Tuple worldToObject(const util::Tuple &point) const;
  virtual util::Tuple normalToWorld(const util::Tuple &vector) const;
  virtual rt::AABB bounds() const = 0;
  virtual rt::AABB parentSpaceBounds() const;
  virtual ~Shape() = default;
  Shape(const Shape &copyFrom) = default;
  Shape(Shape &&moveFrom) = default;
  Shape& operator=(const Shape &assignFrom) = default;
  Shape& operator=(Shape &&moveFrom) = default;
  virtual Intersections localIntersect(const Ray &ray) const = 0;
  virtual util::Tuple localNormalAt(const util::Tuple &point, const rt::Intersection &intersection) const = 0;
protected:
  unsigned m_id;
  rt::Material m_material;
  util::Matrixd m_transform;
  static unsigned m_objCounter;
  util::Tuple m_origin;
  std::weak_ptr<Shape> m_parent;
};

}


#endif//MYPROJECT_SHAPE_H

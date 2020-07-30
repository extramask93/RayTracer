//
// Created by damian on 29.07.2020.
//

#ifndef MYPROJECT_CSG_H
#define MYPROJECT_CSG_H
#include <shapes/Shape.h>

namespace rt {

enum class CSGOpType {
  kUnion,
  kDifference,
  kIntersection
};

class Csg : public rt::Shape, public std::enable_shared_from_this<rt::Csg>
{
public:
  static std::shared_ptr<Csg> createCsg(const CSGOpType &opType, std::shared_ptr<Shape> left, std::shared_ptr<Shape> right);
  const rt::CSGOpType& operation() const;
  Intersections filterIntersections(const Intersections &xs) const;
  bool includes(const Shape * left, const Shape * object) const;
  static bool intersectionAllowed(const CSGOpType &op, bool lhit, bool inl, bool inr);
  const Shape *  left() const;
  const Shape *  right() const;
  AABB bounds() const override;
  Intersections localIntersect(const Ray &ray) const override;
  util::Tuple localNormalAt(const util::Tuple &point, const Intersection &intersection) const override;
  Csg(const CSGOpType &opType, std::shared_ptr<Shape> left, std::shared_ptr<Shape> right);
protected:
  std::shared_ptr<rt::Shape> m_left;
  std::shared_ptr<rt::Shape> m_right;
  rt::CSGOpType m_csgOpType;
};
}


#endif//MYPROJECT_CSG_H

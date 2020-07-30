//
// Created by damian on 22.07.2020.
//

#ifndef MYPROJECT_GROUP_H
#define MYPROJECT_GROUP_H
#include <shapes/Shape.h>
#include <vector>
#include <memory>
namespace rt {
class Group : public Shape, public std::enable_shared_from_this<Group>
{
public:
  explicit Group();
  bool empty() const;
  rt::Group& addChild(const std::shared_ptr<Shape> &child);
  std::vector<std::shared_ptr<Shape>>& children();
  const std::vector<std::shared_ptr<Shape>>& children() const;
  Intersections localIntersect(const Ray &ray) const override;
  util::Tuple localNormalAt(const util::Tuple &point, const rt::Intersection &intersection) const override;
  AABB bounds() const override;

protected:
  std::vector<std::shared_ptr<Shape>> m_childrenList;
};
}// namespace rt

#endif//MYPROJECT_GROUP_H

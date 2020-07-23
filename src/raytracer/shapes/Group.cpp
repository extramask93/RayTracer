//
// Created by damian on 22.07.2020.
//

#include "Group.h"
#include <intersections/Intersections.h>
rt::Intersections rt::Group::localIntersect(const rt::Ray &ray) const
{
  auto xs = rt::Intersections{};
  for(const auto &child : m_childrenList) {
    auto it = child->intersect(ray); // why not local?
    xs.insert(xs.end(),it.begin(),it.end());
  }
  return xs;
}
util::Tuple rt::Group::localNormalAt(const util::Tuple &point) const
{
  (void)point;
  throw std::runtime_error("Calling normal At for a group is illegal");
}
rt::Group::Group() : Shape()
{
}
bool rt::Group::empty() const
{
  return m_childrenList.empty();
}
rt::Group& rt::Group::addChild(const std::shared_ptr<Shape> &child)
{
  auto &added =  m_childrenList.emplace_back(child);
  added->setParent(std::static_pointer_cast<rt::Shape>(shared_from_this()));
  return *this;
}
rt::AABB rt::Group::bounds() const
{
  return rt::AABB();
}

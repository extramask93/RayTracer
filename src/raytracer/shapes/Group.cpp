//
// Created by damian on 22.07.2020.
//

#include "Group.h"
#include <intersections/Intersections.h>
#include <misc/AABB.h>
rt::Intersections rt::Group::localIntersect(const rt::Ray &ray) const
{
  auto xs = rt::Intersections{};
  auto b = bounds();
  if(b.intersect(ray)) {
    for (const auto &child : m_childrenList) {
      auto it = child->intersect(ray);// why not local?
      xs.insert(xs.end(), it.begin(), it.end());
    }
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
  //convert bounds of all objects into group space
  std::vector<rt::AABB> transformedBounds;
  for(const auto &child: m_childrenList) {
    auto bounds = child->parentSpaceBounds();
    transformedBounds.push_back(bounds);
  }
    //convert a point from object space to its parent space, thus multiply the point by the object's transformation matrix
    //when transforming an entire bounding box, first transform all eight of the cube's corners and then find single
    //bounding box that fits them all

  //combine them into single bounding box
  auto newaabb = rt::AABB();
  for(const auto& bound : transformedBounds) {
    newaabb.add(bound);
  }
  return newaabb;
}

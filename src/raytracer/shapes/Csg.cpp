//
// Created by damian on 29.07.2020.
//

#include "Csg.h"
#include <intersections/Intersections.h>
#include <shapes/Group.h>
#include <queue>
rt::Csg::Csg(const rt::CSGOpType &opType, std::shared_ptr<Shape> left, std::shared_ptr<Shape> right) : m_left(left), m_right(right), m_csgOpType(opType)
{
  /*create dummy shared ptr with no deleter from this to prevent destroying the instance */
  /*auto ptr = std::shared_ptr<rt::Csg>( this, [](rt::Csg*){} );
  m_right->setParent(std::static_pointer_cast<rt::Shape>(shared_from_this()));
  m_left->setParent(std::static_pointer_cast<rt::Shape>(shared_from_this()));
*/}
  const rt::CSGOpType &rt::Csg::operation() const
  {
    return m_csgOpType;
  }
  const rt::Shape * rt::Csg::left() const
  {
    return m_left.get();
  }
  const rt::Shape * rt::Csg::right() const
  {
    return m_right.get();
  }
  rt::AABB rt::Csg::bounds() const
  {
    return rt::AABB();
  }
  rt::Intersections rt::Csg::localIntersect(const rt::Ray &ray) const
  {
    auto result = Intersections{};
    auto leftxs = left()->intersect(ray);
    auto rightxs = right()->intersect(ray);
    result.insert(result.end(),leftxs.begin(),leftxs.end());
    result.insert(result.end(), rightxs.begin(),rightxs.end());
    return filterIntersections(result);
  }
  util::Tuple rt::Csg::localNormalAt(const util::Tuple &point, const rt::Intersection &intersection) const
  {
    (void)point;
    (void)intersection;
    return util::Tuple();
  }
  std::shared_ptr<rt::Csg> rt::Csg::createCsg(const CSGOpType &opType, std::shared_ptr<Shape> left, std::shared_ptr<Shape> right)
  {
    auto csg = std::make_shared<Csg>(opType, left, right);
    csg->m_left->setParent(csg);
    csg->m_right->setParent(csg);
    return csg;
  }
  bool rt::Csg::intersectionAllowed(const rt::CSGOpType &op, bool lhit, bool inl, bool inr)
  {
    if (op == CSGOpType::kUnion) {
      return (lhit && !inr) || (!lhit && !inl);
    } else if (op == CSGOpType::kIntersection) {
      return (lhit && inr) || (!lhit && inl);
    } else if (op == CSGOpType::kDifference) {
      return (lhit && !inr) || (!lhit && inl);
    }
    return false;
  }
  bool rt::Csg::includes(const rt::Shape * left,const rt::Shape * object) const
  {
    /*DFS implementation*/
    if(left == nullptr || object == nullptr) {
      return false;
    }
    std::queue<const Shape *> nodes;
    nodes.push(left);
    while (!nodes.empty()) {
      auto currentNode = nodes.back();
      nodes.pop();
      if(currentNode == object) {
        return true;
      }
      if (auto group = dynamic_cast<const rt::Group*>(currentNode)) {
        for (auto &child : group->children()) {
          nodes.push(child.get());
        }
      }
      if(auto csg = dynamic_cast<const rt::Csg*>(currentNode)) {
        nodes.push(csg->left());
        nodes.push(csg->right());
      }
    }
    return false;
  }
  rt::Intersections rt::Csg::filterIntersections(const rt::Intersections &xs) const
  {
    bool inl = false;
    bool inr = false;
    auto result = Intersections{};
    for (const auto &i : xs) {
      auto lhit = includes(left(),i.object());
      if (intersectionAllowed(operation(), lhit, inl, inr)) {
        result.push_back(i);
      }
      if (lhit) {
        inl = !inl;
      } else {
        inr = !inr;
      }
    }
    return result;
  }

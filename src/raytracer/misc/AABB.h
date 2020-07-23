//
// Created by damian on 23.07.2020.
//

#ifndef MYPROJECT_AABB_H
#define MYPROJECT_AABB_H
#include <Tuple.h>
#include <Math.h>
namespace rt {
class AABB
{
public:
  explicit AABB(const util::Tuple &pmin, const util::Tuple &pmax);
  explicit AABB() = default;
  AABB& add(const util::Tuple &point);
  const util::Tuple& min() const;
  const util::Tuple& max() const;
  util::Tuple& min() ;
  util::Tuple& max() ;
  bool operator==(const rt::AABB &other) const;
protected:
  util::Tuple m_min = util::Tuple::point(math::inf<>, math::inf<>, math::inf<>);
  util::Tuple m_max = util::Tuple::point(math::ninf<>,math::ninf<>,math::ninf<>);
};
}// namespace rt

#endif//MYPROJECT_AABB_H

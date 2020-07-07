//
// Created by damian on 06.07.2020.
//

#include "Intersection.h"
using namespace rt;
Intersection::Intersection(double t, const Shape * shape):  m_shape(shape), m_t(t)
{
}
bool Intersection::operator==(const Intersection &other) const
{
  return (m_t == other.m_t) && (*m_shape == *other.m_shape);
}
bool Intersection::operator<(const Intersection &other) const
{
  return m_t < other.m_t;
}
std::optional<Intersection> Intersections::hit()
{
  auto iter = std::find_if(this->begin(),this->end(),[](auto i){ return i.t() > 0 ;});
  if(iter == this->end()) {
    return std::nullopt;
  } else {
    return std::optional<Intersection>(*iter);
  }

}
Intersections::Intersections(const std::initializer_list<Intersection> &elems) : std::vector<Intersection>(elems)
{
  std::sort(this->begin(),this->end(), std::less<Intersection>());
}

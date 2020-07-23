//
// Created by damian on 23.07.2020.
//

#include "AABB.h"
#include <misc/Computations.h>
const util::Tuple &rt::AABB::min() const
{
  return m_min;
}
const util::Tuple &rt::AABB::max() const
{
  return m_max;
}
rt::AABB::AABB(const util::Tuple &pmin, const util::Tuple &pmax) : m_min(pmin), m_max(pmax)
{
}
rt::AABB &rt::AABB::add(const util::Tuple &point)
{
  if(point.x() > m_max.x()) m_max.x() = point.x();
  if(point.y() > m_max.y()) m_max.y() = point.y();
  if(point.z() > m_max.z()) m_max.z() = point.z();
  if(point.x() < m_min.x()) m_min.x() = point.x();
  if(point.y() < m_min.y()) m_min.y() = point.y();
  if(point.z() < m_min.z()) m_min.z() = point.z();
  return *this;
}
bool rt::AABB::operator==(const rt::AABB &other) const
{
  return (m_min == other.m_min) && (m_max == other.m_max);
}
util::Tuple &rt::AABB::min()
{
  return m_min;
}
util::Tuple &rt::AABB::max()
{
  return m_max;
}

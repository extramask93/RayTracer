//
// Created by damian on 23.07.2020.
//

#include "AABB.h"
#include <misc/Computations.h>
#include <ray/Ray.h>
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
rt::AABB rt::AABB::transform(const util::Matrixd &transform)
{
  auto newAABB = rt::AABB();
  auto s = m_max - m_min;
  newAABB.add(transform * util::Tuple::point(m_max.x() - s.x(), m_max.y(), m_max.z()));
  newAABB.add(transform * util::Tuple::point(m_max.x() - s.x(), m_max.y() - s.y(), m_max.z()));
  newAABB.add(transform * util::Tuple::point(m_max.x() , m_max.y() - s.y(), m_max.z()));
  newAABB.add(transform * m_max);
  newAABB.add(transform * util::Tuple::point(m_min.x(), m_min.y() + s.y(), m_min.z()));
  newAABB.add(transform * util::Tuple::point(m_min.x() + s.x(), m_min.y() + s.y(), m_min.z()));
  newAABB.add(transform * util::Tuple::point(m_min.x() + s.x(), m_min.y(), m_min.z()));
  newAABB.add(transform * m_min);
  return newAABB;

}
rt::AABB &rt::AABB::add(const rt::AABB &box)
{
  return add(box.min()).add(box.max());
}
std::pair<double, double> rt::AABB::checkAxis(double origin, double direction, double min, double max) const
{
  auto tmin_numerator = (min - origin);
  auto tmax_numerator = (max-origin);
  double tmin,tmax;
  if constexpr (std::numeric_limits<double>::is_iec559) {
    tmin = tmin_numerator / direction;
    tmax = tmax_numerator / direction;
  } else {
    if (std::fabs(direction) >= EPSILON) {
      tmin = tmin_numerator / direction;
      tmax = tmax_numerator / direction;
    } else {
      tmin = tmin_numerator * std::numeric_limits<double>::infinity();
      tmax = tmax_numerator * std::numeric_limits<double>::infinity();
    }
  }
  if(tmin > tmax) {
    std::swap(tmin,tmax);
  }
  return std::make_pair(tmin,tmax);

}
bool rt::AABB::intersect(const rt::Ray &ray) const
{
  auto [xtmin,xtmax] = checkAxis(ray.origin().x(), ray.direction().x(), m_min.x(), m_max.x());
  auto [ytmin,ytmax] = checkAxis(ray.origin().y(), ray.direction().y(), m_min.y(), m_max.y());
  auto [ztmin,ztmax] = checkAxis(ray.origin().z(), ray.direction().z(), m_min.z(), m_max.z());
  auto tmin = std::max({xtmin,ytmin,ztmin});
  auto tmax = std::min({xtmax,ytmax,ztmax});
  return tmin <= tmax;
}

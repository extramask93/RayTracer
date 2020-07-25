//
// Created by damian on 06.07.2020.
//

#include "Shape.h"
#include <intersections/Intersection.h>
#include <intersections/Intersections.h>
namespace rt {
unsigned Shape::m_objCounter = 0;
Shape::Shape() : m_id(m_objCounter), m_material(rt::Material()), m_transform(util::Matrixd::Identity(4)),
                 m_origin(util::Tuple::point(0, 0, 0))
{
  m_objCounter++;
}
bool Shape::operator==(const Shape &other) const
{
  return m_id == other.m_id;
}
const rt::Material &Shape::material() const
{
  return m_material;
}
rt::Material &Shape::material()
{
  return m_material;
}
void Shape::setMaterial(const Material &mat)
{
  m_material = mat;
}
void rt::Shape::setTransform(const util::Matrixd &transorm)
{
  m_transform = transorm;
}

const util::Matrixd &rt::Shape::transform() const
{
  return m_transform;
}
Intersections Shape::intersect(const Ray &ray) const
{
  auto rayInObjectSpace = ray.transform(m_transform.inverse());
  return localIntersect(rayInObjectSpace);
}
util::Tuple Shape::normalAt(const util::Tuple &point) const
{
  /*auto worldToObjectSpaceTransform = m_transform.inverse();
  auto objectSpacePoint = worldToObjectSpaceTransform * point;
*/
  const auto localPoint = worldToObject(point);
  const auto localNormal = localNormalAt(localPoint);
  return normalToWorld(localNormal);
  /*auto worldNormal = m_transform.inverse().transpose() * objectNormal;
  worldNormal.w() = 0;
  return worldNormal.normalize();*/
}
util::Matrixd &Shape::transform()
{
  return m_transform;
}
const std::shared_ptr<const Shape> Shape::parent() const
{
  return m_parent.lock();
}
void Shape::setParent(const std::shared_ptr<Shape> &parent)
{
  m_parent = parent;
}
util::Tuple Shape::worldToObject(const util::Tuple &point) const
{
  auto parentSpacePoint = point;
  if (parent() != nullptr) {
    parentSpacePoint = parent()->worldToObject(point);
  }
  return m_transform.inverse() * parentSpacePoint;
}
util::Tuple Shape::normalToWorld(const util::Tuple &vector) const
{
  auto n1 = m_transform.inverse().transpose() * vector;
  auto n2 = util::Tuple::vector(n1.x(),n1.y(),n1.z());
  n2.normalize();
  if(parent() != nullptr) {
    n2 = parent()->normalToWorld(n2);
  }
  return n2;
}
rt::AABB Shape::parentSpaceBounds() const
{
  return bounds().transform(m_transform);
}
}// namespace rt

//
// Created by damian on 06.07.2020.
//

#include "Shape.h"
#include <intersections/Intersection.h>
#include <intersections/Intersections.h>
namespace rt {
  unsigned Shape::m_objCounter = 0;
Shape::Shape() : m_id(m_objCounter), m_material(rt::Material()), m_transform(util::Matrixd::Identity(4)),
                   m_origin(util::Tuple::point(0,0,0))
{
  m_objCounter++;
}
bool Shape::operator==(const Shape &other) const
{
  return m_id == other.m_id;
}
const rt::Material& Shape::material() const
{
  return m_material;
}
rt::Material& Shape::material()
{
  return m_material;
}
void Shape::setMaterial(const Material &mat)
{
  m_material = mat;
}
void rt::Shape::setTransform(const util::Matrixd &transorm)
{
  m_transform=transorm;
}

const util::Matrixd& rt::Shape::transform() const
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
  auto worldToObjectSpaceTransform = m_transform.inverse();
  auto objectSpacePoint = worldToObjectSpaceTransform * point;

  auto objectNormal =  localNormalAt(objectSpacePoint);

  auto worldNormal =  m_transform.inverse().transpose()*objectNormal;
  worldNormal.w() = 0;
  return worldNormal.normalize();
}
util::Matrixd &Shape::transform()
{
  return m_transform;
}
}

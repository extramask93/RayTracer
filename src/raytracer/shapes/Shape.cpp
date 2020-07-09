//
// Created by damian on 06.07.2020.
//

#include "Shape.h"
#include <intersections/Intersection.h>
#include <intersections/Intersections.h>
namespace rt {
  unsigned Shape::m_objCounter = 0;
Shape::Shape() : m_id(m_objCounter), m_material(rt::Material())
{
  m_objCounter++;
}
bool Shape::operator==(const Shape &other) const
{
  return m_id == other.m_id;
}
rt::Material Shape::material() const
{
  return m_material;
}
void Shape::setMaterial(const Material &mat)
{
  m_material = mat;
}
}

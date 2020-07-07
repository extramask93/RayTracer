//
// Created by damian on 06.07.2020.
//

#include "Shape.h"
#include <Intersection.h>
namespace rt {
  unsigned Shape::m_objCounter = 0;
Shape::Shape() : m_id(m_objCounter)
{
  m_objCounter++;
}
bool Shape::operator==(const Shape &other) const
{
  return m_id == other.m_id;
}
}

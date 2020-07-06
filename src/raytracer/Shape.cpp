//
// Created by damian on 06.07.2020.
//

#include "Shape.h"
namespace rt {
  unsigned Shape::m_objCounter = 0;
Shape::Shape() : m_id(m_objCounter)
{
  m_objCounter++;
}
}

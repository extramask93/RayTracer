//
// Created by damian on 29.05.2020.
//

#include "Canvas.h"
namespace util {
std::vector<util::Color>::iterator Canvas::begin()
{
  return m_buffer.begin();
}
std::vector<util::Color>::iterator Canvas::end()
{
  return m_buffer.end();
}
std::vector<util::Color>::const_iterator Canvas::begin() const
{
  return m_buffer.begin();
}
std::vector<util::Color>::const_iterator Canvas::end() const
{
  return m_buffer.end();
}
const Color &Canvas::operator()(unsigned int x, unsigned int y) const
{

  return m_buffer[xyToIndex(x,y)];
}
Color &Canvas::operator()(unsigned int x, unsigned int y)
{
  return m_buffer[xyToIndex(x,y)];
}
}// namespace util
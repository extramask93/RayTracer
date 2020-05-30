//
// Created by damian on 29.05.2020.
//

#ifndef MYPROJECT_CANVAS_H
#define MYPROJECT_CANVAS_H


#include <vector>
#include "Color.h"
namespace util {
class Canvas
{
  using BType = std::vector<Color>;
public:
  explicit Canvas(unsigned width, unsigned height) : m_width(width), m_height(height),
                                                     m_buffer(m_width * m_height, Color(0, 0, 0)) {}
  [[nodiscard]]constexpr unsigned width() const;
  [[nodiscard]]constexpr unsigned height() const;
  [[nodiscard]]Color& operator()(unsigned x,unsigned y);
  [[nodiscard]]const Color& operator()(unsigned x,unsigned y) const;
  BType::const_iterator begin() const;
  BType::const_iterator end() const;
  BType::iterator begin();
  BType::iterator end();
private:
  [[nodiscard]] constexpr unsigned xyToIndex(unsigned  x, unsigned y) const;
  const unsigned m_width;
  const unsigned m_height;
  BType m_buffer;
};


constexpr unsigned Canvas::width() const
{
  return m_width;
}

constexpr unsigned Canvas::height() const
{
  return m_height;
}

constexpr unsigned Canvas::xyToIndex(unsigned int x, unsigned int y) const
{
  return y*m_width + x;
}
}// namespace util
#endif//MYPROJECT_CANVAS_H

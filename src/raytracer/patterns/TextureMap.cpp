//
// Created by damian on 05.08.2020.
//

#include "TextureMap.h"
#include <misc/Computations.h>
util::Color rt::TextureMap::patternAt(const util::Tuple &point) const
{
  const auto [u,v] = m_uvMap(point);
  return m_uvPattern->uvPatternAt(u,v);
}
rt::Pattern *rt::TextureMap::clone_impl() const
{
  return new TextureMap(*this);
}
rt::TextureMap::TextureMap(rt::Pattern *uv_pattern, std::function<std::pair<double, double>(const util::Tuple &)> uv_map)
: Pattern(util::Color::WHITE, util::Color::BLACK), m_uvPattern(uv_pattern), m_uvMap(uv_map)
{
 // m_uvMap = uv_map;
}

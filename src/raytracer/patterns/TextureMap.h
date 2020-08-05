//
// Created by damian on 05.08.2020.
//

#ifndef MYPROJECT_TEXTUREMAP_H
#define MYPROJECT_TEXTUREMAP_H

#include <patterns/Pattern.h>
namespace rt {
class TextureMap : public Pattern
{
public:
  TextureMap(Pattern *uv_pattern, std::function<std::pair<double,double>(const util::Tuple&)> uv_map);
  util::Color patternAt(const util::Tuple &point) const override;
protected:
  Pattern *clone_impl() const override;
  Pattern *m_uvPattern;
  std::function<std::pair<double,double>(const util::Tuple&)> m_uvMap;
};
}


#endif//MYPROJECT_TEXTUREMAP_H

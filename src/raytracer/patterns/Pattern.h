//
// Created by damian on 14.07.2020.
//

#ifndef MYPROJECT_PATTERN_H
#define MYPROJECT_PATTERN_H
#include <Matrix.h>
#include <Color.h>
#include <memory>
namespace rt {
class Pattern
{
public:
  explicit Pattern(const util::Color &a, const util::Color &b);
  [[nodiscard]] virtual util::Color a() const;
  [[nodiscard]] virtual util::Color b() const;
  [[nodiscard]] virtual const util::Matrixd& transform() const;
  [[nodiscard]] virtual util::Matrixd& transform() ;
  [[nodiscard]] virtual util::Color patternAt(const util::Tuple &point) const = 0;
  auto clone() const { return std::unique_ptr<Pattern>(clone_impl()); }
public:
  virtual ~Pattern() = default;
  Pattern(const Pattern &other) = default;
  Pattern(Pattern &&other) noexcept = default;
  Pattern& operator=(const Pattern &other) = default;
  Pattern& operator=(Pattern &&other) noexcept = default;
protected:
  virtual Pattern* clone_impl() const = 0;
protected:
  util::Color m_a;
  util::Color m_b;
  util::Matrixd m_transform;
};
}


#endif//MYPROJECT_PATTERN_H

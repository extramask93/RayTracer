//
// Created by damian on 26.07.2020.
//

#ifndef MYPROJECT_OBJPARSER_H
#define MYPROJECT_OBJPARSER_H
#include <Tuple.h>
#include <vector>
#include <map>
#include <shapes/Triangle.h>

namespace rt {
class Group;
class ObjParser
{
public:
  std::size_t linesIgnored() const;
  std::shared_ptr<rt::Group> objToGroup() const;
  std::vector<util::Tuple>& vertices();
  std::vector<util::Tuple>& normals();
  std::map<std::string, std::shared_ptr<rt::Group>>& groups();
  std::shared_ptr<rt::Group> defaultGroup();
  static ObjParser fromStream(std::istream &ss);

protected:
  std::vector<std::shared_ptr<rt::Shape>>
    fanTriangulation(const std::vector<std::pair<std::size_t, std::optional<std::size_t>>> &verticesIdx);
protected:
  std::vector<util::Tuple> m_vertices{util::Tuple::point(0,0,0)};
  std::vector<util::Tuple> m_normals{util::Tuple::vector(0,0,0)};
  std::shared_ptr<rt::Group> m_defaultGroup = std::make_shared<rt::Group>();
  std::map<std::string, std::shared_ptr<rt::Group>> m_groups;
  std::size_t m_linesIgnored = 0;
};
}// namespace rt


#endif//MYPROJECT_OBJPARSER_H

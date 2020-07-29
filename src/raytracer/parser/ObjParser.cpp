//
// Created by damian on 26.07.2020.
//

#include <istream>
#include <regex>
#include <iostream>
#include <string>
#include <shapes/Triangle.h>
#include <shapes/Group.h>
#include <shapes/SmoothTriangle.h>
#include "ObjParser.h"
#define VERT_PATTERN R"(^(v)\s+(-?\d+\.*\d*)\s+(-?\d+\.*\d*)\s+(-?\d+\.*\d*)(\s+-?\d+\.*\d*)?)"
#define FACE_PATTERN R"(^(f)((\s+(\d+(\/\d*)*)){3,}))"
#define INNER_FACE_PATTERN R"((\d+)(\/?\d*)+)"
#define INNER_NORMAL_PATTERN R"((\d+)*\/(\d+)(\s|$))"
#define NORMALS_PATTERN R"(^(vn)\s+(-?\d+\.*\d*)\s+(-?\d+\.*\d*)\s+(-?\d+\.*\d*)(\s+-?\d+\.*\d*)?)"
#define GROUP_PATTERN R"(^(g)\s+([a-zA-z]+))"
rt::ObjParser rt::ObjParser::fromStream(std::istream &ss)
{
  rt::ObjParser result;
  std::shared_ptr<rt::Group> currentGroup = result.defaultGroup();
  for (std::string line; std::getline(ss, line);) {
    std::smatch sm;
    std::regex e(VERT_PATTERN);
    std::regex e2(FACE_PATTERN);
    std::regex e3(GROUP_PATTERN);
    std::regex e4(NORMALS_PATTERN);
    if (std::regex_search(line, sm, e)) {
      util::Tuple vertex = util::Tuple::point(0, 0, 0);
      vertex.x() = std::stod(sm[2]);
      vertex.y() = std::stod(sm[3]);
      vertex.z() = std::stod(sm[4]);
      result.m_vertices.emplace_back(vertex);
    } else if(std::regex_search(line,sm,e4)) {
      util::Tuple normal = util::Tuple::vector(0,0,0);
      normal.x() = std::stod(sm[2]);
      normal.y() = std::stod(sm[3]);
      normal.z() = std::stod(sm[4]);
      result.m_normals.emplace_back(normal);
    }
    else if (std::regex_search(line, sm, e2)) {
      std::vector<std::pair<size_t, std::optional<std::size_t>>> vertices;
      std::size_t i;
      std::regex r(INNER_FACE_PATTERN);
      std::smatch sm2;
      std::string inner = sm[2];
      while(regex_search(inner, sm2, r))
      {
        i = std::stoul(sm2.str());
        vertices.push_back(std::make_pair(i,std::nullopt));
        inner = sm2.suffix();
      }
      inner = sm[2];
      std::regex r2(INNER_NORMAL_PATTERN);
      std::size_t counter = 0;
      while(regex_search(inner,sm2,r2)) {
        auto str = sm2[sm2.size()-2].str();
          i = std::stoul(sm2[sm2.size()-2].str());
          vertices[counter++].second = i;
          inner = sm2.suffix();
      }
      auto shapes = result.fanTriangulation(vertices);
      for (auto shape : shapes) {
        currentGroup->addChild(shape);
      }
    } else if (std::regex_search(line, sm, e3)) {
      auto [iter,res] = result.groups().emplace(std::make_pair(sm[2], std::make_shared<rt::Group>()));
      currentGroup = iter->second;
    } else {
      result.m_linesIgnored++;
    }
  }
  return result;
}
std::size_t rt::ObjParser::linesIgnored() const
{
  return m_linesIgnored;
}
std::vector<util::Tuple> &rt::ObjParser::vertices()
{
  return m_vertices;
}
std::shared_ptr<rt::Group> rt::ObjParser::defaultGroup()
{
  return m_defaultGroup;
}
std::vector<std::shared_ptr<rt::Shape>>
  rt::ObjParser::fanTriangulation(const std::vector<std::pair<std::size_t, std::optional<std::size_t>>> &verticesIdx)
{
  std::vector<std::shared_ptr<rt::Shape>> triangles;
  for (unsigned i = 1; i < verticesIdx.size() - 1; i++) {
    std::shared_ptr<rt::Shape> triangle;
    if(verticesIdx[i].second == std::nullopt) {
      triangle = std::make_shared<rt::Triangle>(m_vertices[1], m_vertices[verticesIdx[i].first], m_vertices[verticesIdx[i + 1].first]);
    } else {
      triangle = std::make_shared<rt::SmoothTriangle>(m_vertices[1],m_vertices[verticesIdx[i].first], m_vertices[verticesIdx[i + 1].first],
        m_normals[verticesIdx[i-1].second.value()], m_normals[verticesIdx[i].second.value()], m_normals[verticesIdx[i+1].second.value()]);
    }
    triangles.emplace_back(triangle);
  }
  return triangles;
}
std::map<std::string, std::shared_ptr<rt::Group>> &rt::ObjParser::groups()
{
  return m_groups;
}
std::shared_ptr<rt::Group> rt::ObjParser::objToGroup() const
{
  auto parent = std::make_shared<rt::Group>();
  parent->addChild(m_defaultGroup);
  for(const auto [str,child] : m_groups) {
    parent->addChild(child);
  }
  return parent;
}
std::vector<util::Tuple> &rt::ObjParser::normals()
{
  return m_normals;
}

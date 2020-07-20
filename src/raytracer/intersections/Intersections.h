//
// Created by damian on 09.07.2020.
//

#ifndef MYPROJECT_INTERSECTIONS_H
#define MYPROJECT_INTERSECTIONS_H
#include <vector>
#include <initializer_list>
#include <optional>
#include <intersections/Intersection.h>
namespace rt {

class Intersections : public std::vector<Intersection>
{
public:
  explicit Intersections(const std::initializer_list<Intersection> &elems);
  iterator insert(const_iterator pos, const_iterator first, const_iterator last);
  std::optional<Intersection> hit() const;
};

}// namespace rt


#endif//MYPROJECT_INTERSECTIONS_H

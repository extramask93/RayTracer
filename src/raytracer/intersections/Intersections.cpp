//
// Created by damian on 09.07.2020.
//

#include "Intersections.h"
using namespace rt;
std::optional<Intersection> Intersections::hit() const
{
  auto iter = std::find_if(this->begin(),this->end(),[](auto i){ return i.t() > 0 ;});
  if(iter == this->end()) {
    return std::nullopt;
  } else {
    return std::optional<Intersection>(*iter);
  }

}
Intersections::Intersections(const std::initializer_list<Intersection> &elems) : std::vector<Intersection>(elems)
{
  std::sort(this->begin(),this->end(), std::less<Intersection>());
}
std::vector<Intersection>::iterator Intersections::insert(std::vector<Intersection>::const_iterator pos, std::vector<Intersection>::const_iterator first, std::vector<Intersection>::const_iterator last)
{
  auto it = std::vector<Intersection>::insert(pos,first,last);
  std::sort(this->begin(),this->end(), std::less<Intersection>());
  return it;
}

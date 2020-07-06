//
// Created by damian on 06.07.2020.
//

#include "Intersection.h"
using namespace rt;
std::size_t Intersection::count() const
{
  return m_ticks.size();
}
double Intersection::operator[](unsigned int index) const
{
  return m_ticks[index];
}
Intersection::Intersection(std::initializer_list<double> ticks) : m_ticks(ticks)
{
  std::sort(m_ticks.begin(), m_ticks.end(),std::less<double>());
}

std::vector<Intersection> Intersections(std::initializer_list<Intersection> intersections){
  return std::vector<Intersection>(intersections);
}

//
// Created by damian on 09.07.2020.
//

#include "World.h"
#include <shapes/Sphere.h>
#include <materials/Material.h>
namespace rt {
std::unique_ptr<World> rt::World::defaultWorld()
{
  auto sphere1 = std::make_unique<Sphere>(Sphere());
  auto material1 = rt::Material();
  material1.setColor(util::Color(0.8,1.0,0.6));
  material1.setDiffuse(0.7);
  material1.setSpecular(0.2);
  sphere1->setMaterial(material1);
  auto sphere2 = std::make_unique<Sphere>(Sphere());
  sphere2->setTransform(util::Matrixd::scaling(0.5,0.5,0.5));
  auto light = std::make_unique<PointLight>(
    PointLight(util::Tuple::point(-10,10,-10),util::Color(1,1,1)));
  auto result = std::make_unique<World>(World());
  result->m_shapes.emplace_back(std::move(sphere1));
  result->m_shapes.emplace_back(std::move(sphere2));
  result->m_lights.emplace_back(std::move(light));
  return result;
}

std::vector<std::unique_ptr<Shape>> &World::shapes() const
{
  return m_shapes;
}
std::vector<std::unique_ptr<PointLight>> &World::lights() const
{
  return m_lights;
}
Intersections World::intersect(const Ray &ray) const
{
  auto intersections = Intersections{};
  for(const auto &shape : m_shapes) {
    auto shapeIntersections = shape->intersect(ray);
    intersections.insert(intersections.end(), shapeIntersections.begin(), shapeIntersections.end());
  }
  return intersections;
}
}// namespace rt

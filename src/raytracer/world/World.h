//
// Created by damian on 09.07.2020.
//

#ifndef MYPROJECT_WORLD_H
#define MYPROJECT_WORLD_H
#include <optional>
#include <vector>
#include <memory>
#include <Matrix.h>
#include <shapes/Shape.h>
#include <lights/PointLight.h>
namespace rt {
class World : public IIntersect
{
public:
  static std::unique_ptr<World> defaultWorld();
  [[nodiscard]] std::vector<std::unique_ptr<PointLight>>& lights() const;
  [[nodiscard]] std::vector<std::shared_ptr<Shape>>& shapes() const;
  Intersections intersect(const Ray &ray) const override;

private:
  mutable std::vector<std::unique_ptr<PointLight>> m_lights;
  mutable std::vector<std::shared_ptr<Shape>> m_shapes;
};
}// namespace rt


#endif//MYPROJECT_WORLD_H

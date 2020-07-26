//
// Created by damian on 07.07.2020.
//
#include <Matrix.h>
#include <CanvasPrinter.h>
#include <Canvas.h>
#include <ray/Ray.h>
#include <shapes/Sphere.h>
#include <materials/Material.h>
#include <lights/PointLight.h>
#include <misc/Computations.h>
#include <intersections/Intersection.h>
#include <intersections/Intersections.h>
#include <shapes/Plane.h>
#include <patterns/LinearGradientPattern.h>
#include <patterns/RingPattern.h>
#include <patterns/RadialGradientPattern.h>
#include <shapes/Cone.h>
#include <shapes/Group.h>
auto hexagonCorner() {
  auto corner = std::make_shared<rt::Sphere>();
  corner->setTransform(util::Matrixd::translation(0,0,-1) * util::Matrixd::scaling(0.25,0.25,0.25));
  return corner;
}
auto hexagonEdge() {
  auto edge = std::make_shared<rt::Cylinder>();
  edge->minimum() = 0;
  edge->maximum() = 1;
  edge->setTransform(util::Matrixd::translation(0,0,-1) * util::Matrixd::rotation_y(math::pi<>/-6) *
                     util::Matrixd::rotation_z(math::pi<>/-2) * util::Matrixd::scaling(0.25,1,0.25));
  return edge;
}
auto hexagonSide() {
  auto side = std::make_shared<rt::Group>();
  side->addChild(hexagonCorner());
  side->addChild(hexagonEdge());
  return side;
}
auto hexagon() {
  auto hex = std::make_shared<rt::Group>();
  for(int i =0; i < 5 ; i++) {
    auto side = hexagonSide();
    side->setTransform(util::Matrixd::rotation_y(i*math::pi<>/3));
    hex->addChild(side);
  }
  return hex;
}
int main(int argc, const char **argv)
{
  (void)argc;
  (void)argv;
  auto world = rt::World();
  auto cone = rt::Cone();
  /*cone.maximum() = 0.5;
  cone.minimum() = 0;
  cone.setTransform(util::Matrixd::translation(-1,0,0.5) *util::Matrixd::scaling(1,3,1)
                    );
  world.shapes().emplace_back(std::make_unique<rt::Cone>(cone));
  /////////////////////////////////////////////////////////////////
  auto sphere2 = std::make_unique<rt::Sphere>();
  sphere2->setTransform(util::Matrixd::translation(-1.25,1.5,0.5)*util::Matrixd::scaling(0.25,0.25,0.25));
  sphere2->setMaterial(rt::Material()
                         .setColor(util::Color(0.5, 0, 0))
                         .setDiffuse(0.7)
                         .setSpecular(0.3));
  world.shapes().emplace_back(std::move(sphere2));
  ////////////////////////////////////////////////////////////////
  auto sphere3 = std::make_unique<rt::Sphere>();
  sphere3->setTransform(util::Matrixd::translation(1.5,0.5,1)*util::Matrixd::scaling(0.5,0.5,0.5));
  world.shapes().emplace_back(std::move(sphere3));
  ///////////////////////////////////////////////////////////////
  auto floor = std::make_unique<rt::Plane>();
  //floor->setTransform(util::Matrixd::scaling(10,0.01,10));
  floor->setMaterial(rt::Material()
                         .setColor(util::Color(1, 0.9, 0.9))
                         .setSpecular(0));
  world.shapes().emplace_back(std::move(floor));
  ///////////////////////////////////////////////////////////////
  auto wall = std::make_unique<rt::Plane>();
  wall->setTransform(util::Matrixd::translation(0,0,10) *util::Matrixd::rotation_x(std::numbers::pi/2));
  wall->setMaterial(rt::Material()
                       .setColor(util::Color(0.5, 0.9, 0.9))
                       .setSpecular(0));
  world.shapes().emplace_back(std::move(wall));*/
  /////////////////////////////////////////////////////////////
  world.shapes().emplace_back(hexagon());
  auto light = std::make_unique<rt::PointLight>(util::Tuple::point(-10, 10, -10),
    util::Color(1, 1, 1));
  world.lights().emplace_back(std::move(light));

  auto camera = rt::Camera(200, 100, std::numbers::pi / 3);
  auto transform = rt::viewTransformation(util::Tuple::point(0,1.5,-4),util::Tuple::point(0,0,0),util::Tuple::vector(0,1,0));
  camera.setTransform(transform);

  util::Canvas canvas = rt::render(camera, world);
  auto printer = util::CanvasPrinter();
  printer.printToPPM(std::filesystem::current_path() / "sphere2.ppm", canvas);
}

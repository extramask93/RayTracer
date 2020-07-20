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
//const double wall_z = 10;
//const double ray_z = -4;
const unsigned canvas_size = 300;
const double wall_size = 12;
//const double pixel_size = wall_size / canvas_size;
//const double half = wall_size / 2;
int main(int argc, const char **argv)
{
  (void)argc;
  (void)argv;
  auto world = rt::World();
  auto sphere1 = std::make_unique<rt::Sphere>();
  sphere1->setTransform(util::Matrixd::translation(-0.5, 1.0, 0.5));
  sphere1->setMaterial(rt::Material()
                         .setColor(util::Color(0.1, 1.0, 0.5))
                         .setDiffuse(0.7)
                         .setSpecular(0.3).setPattern(std::make_unique<rt::RadialGradientPattern>(util::Color(1,1,1),
                           util::Color(0,0,0))));
  sphere1->material().pattern()->transform() = util::Matrixd::rotation_x(std::numbers::pi/2)*util::Matrixd::scaling(1,1,1);
  world.shapes().emplace_back(std::move(sphere1));
  /////////////////////////////////////////////////////////////////
  auto sphere2 = std::make_unique<rt::Sphere>();
  sphere2->setTransform(util::Matrixd::translation(-1,0,1)*util::Matrixd::scaling(0.5,0.5,0.5));
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
  world.shapes().emplace_back(std::move(wall));
  /////////////////////////////////////////////////////////////
  auto light = std::make_unique<rt::PointLight>(util::Tuple::point(-10, 10, -10),
    util::Color(1, 1, 1));
  world.lights().emplace_back(std::move(light));

  auto camera = rt::Camera(200, 100, std::numbers::pi / 3);
  auto transform = rt::viewTransformation(util::Tuple::point(0,1.5,-4),util::Tuple::point(0,1,0),util::Tuple::vector(0,1,0));
  camera.setTransform(transform);

  util::Canvas canvas = rt::render(camera, world);
  auto printer = util::CanvasPrinter();
  printer.printToPPM(std::filesystem::current_path() / "sphere2.ppm", canvas);
}

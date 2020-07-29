//
// Created by damian on 27.07.2020.
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
#include <parser/ObjParser.h>
#include <fstream>
int main(int argc, const char **argv)
{
  (void)argc;
  (void)argv;
  auto world = rt::World();
  std::fstream f("/home/damian/RayTracer/resources/teapot.obj", std::fstream::in);
  auto parser = rt::ObjParser::fromStream(f);
  auto light = std::make_unique<rt::PointLight>(util::Tuple::point(-10, 10, -10),
                                                util::Color(1, 1, 1));
  world.lights().emplace_back(std::move(light));
  world.shapes().emplace_back(parser.objToGroup());
  world.shapes().back()->setTransform(util::Matrixd::scaling(0.25,0.25,0.25)*util::Matrixd::rotation_x(-math::pi<>/2));
  auto camera = rt::Camera(200, 100, std::numbers::pi / 3);
  auto transform = rt::viewTransformation(util::Tuple::point(0,1.5,-20),util::Tuple::point(0,0,0),util::Tuple::vector(0,1,0));
  camera.setTransform(transform);
  util::Canvas canvas = rt::render(camera, world);
  auto printer = util::CanvasPrinter();
  printer.printToPPM(std::filesystem::current_path() / "teapot.ppm", canvas);
}

//
// Created by damian on 10.07.2020.
//

#ifndef MYPROJECT_COMPUTATIONS_H
#define MYPROJECT_COMPUTATIONS_H
#include <intersections/Intersection.h>
#include <world/World.h>
#include <camera/Camera.h>
#include <Canvas.h>
#include <patterns/StripePattern.h>
#include <intersections/Intersections.h>
#define EPSILON 0.00001
namespace rt {
struct Computations
{
  util::Tuple point;
  util::Tuple eyev;
  util::Tuple normalv;
  util::Tuple overPoint;
  util::Tuple underPoint;
  util::Tuple reflectv;
  double t;
  double n1;
  double n2;
  const Shape *object;
  bool inside;
};
Computations prepareComputations(const Intersection &i, const Ray &ray, const rt::Intersections &intersections = rt::Intersections{});
util::Color colorAt(const World &world, const rt::Ray &ray, short callsLeft=4);
util::Color lighting(const rt::Material &material, const rt::Shape &object, const rt::PointLight &light, const util::Tuple &position, const util::Tuple &eye, const util::Tuple &normal, bool inShadow);
util::Matrixd viewTransformation(const util::Tuple &from, const util::Tuple &to, const util::Tuple &up);
rt::Ray rayForPixel(const rt::Camera &c, unsigned px, unsigned py);
bool isShadowed(const rt::World &world, const util::Tuple &point);
util::Canvas render(const rt::Camera &c, const rt::World &world);
util::Color patternAtObject(const rt::Pattern &pattern, const rt::Shape &shape, const util::Tuple &point);
util::Color reflectedColor(const rt::World &world, const rt::Computations &comps, short callsLeft=4);
util::Color refractedColor(const rt::World &world, const rt::Computations &comps, short callsLeft=4);
std::pair<double, double> spherical_map(const util::Tuple &point);
std::pair<double, double> planar_map(const util::Tuple &point);
double schlick(const Computations &comps);
bool equal(double x, double y);
}// namespace rt
#endif//MYPROJECT_COMPUTATIONS_H

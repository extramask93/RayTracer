//
// Created by damian on 10.07.2020.
//

#ifndef MYPROJECT_COMPUTATIONS_H
#define MYPROJECT_COMPUTATIONS_H
#include <intersections/Intersection.h>
#include <world/World.h>
#include <camera/Camera.h>
#include <Canvas.h>
namespace rt {
struct Computations
{
  util::Tuple point;
  util::Tuple eyev;
  util::Tuple normalv;
  double t;
  const Shape* object;
  bool inside;
};
Computations prepareComputations(const Intersection &i, const Ray &ray);
util::Color colorAt(const World &world, const rt::Ray &ray);
util::Matrixd viewTransformation(const util::Tuple &from, const util::Tuple &to, const util::Tuple &up);
rt::Ray rayForPixel(const rt::Camera &c, unsigned px, unsigned py);
util::Canvas render(const rt::Camera &c,const rt::World &world);
}// namespace rt
#endif//MYPROJECT_COMPUTATIONS_H

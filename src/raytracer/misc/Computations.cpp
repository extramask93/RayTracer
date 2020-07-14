//
// Created by damian on 10.07.2020.
//

#include "Computations.h"
#include <intersections/Intersections.h>
#include <misc/Shader.h>
namespace rt {
Computations prepareComputations(const Intersection &i, const Ray &ray){
  Computations comp;
  comp.t = i.t();
  comp.object = i.object();
  comp.point = ray.position(comp.t);
  comp.eyev = -ray.direction();
  comp.normalv = comp.object->normalAt(comp.point);
  comp.inside = false;
  if(comp.normalv.dot(comp.eyev) < 0) {
    comp.inside = true;
    comp.normalv = -comp.normalv;
  }
  comp.overPoint = comp.point + comp.normalv*EPSILON;
  return comp;
}
util::Color colorAt(const World &world, const Ray &ray)
{
  auto result = util::Color::BLACK;
  auto intersections = world.intersect(ray);
  if(intersections.hit().has_value()) {
    auto comps = prepareComputations(intersections.hit().value(), ray);
    result = result + rt::Shader::shadeHit(world, comps);
  }
  return result; //util::Color::BLACK;
}
util::Matrixd viewTransformation(const util::Tuple &from, const util::Tuple &to, const util::Tuple &up)
{
  auto forwardv = (to - from).normalize();
  auto upn = up.normalization();
  auto leftv = forwardv.cross(upn);
  auto trueupv = leftv.cross(forwardv);
  auto orientationm = util::Matrixd(4,4);
  //TODO research where it comes from, scratchpixel.com
  orientationm << leftv.x(), leftv.y(), leftv.z(), 0,
                  trueupv.x(), trueupv.y(), trueupv.z(),0,
                  -forwardv.x(), -forwardv.y(), -forwardv.z(),0,
                  0,0,0,1;

  return orientationm*util::Matrixd::translation(-from.x(), -from.y(), -from.z());
}
rt::Ray rayForPixel(const Camera &c, unsigned int px, unsigned int py)
{
  double xoffset = (px + 0.5) * c.pixelSize();
  double yoffset = (py + 0.5) * c.pixelSize();
  double worldx = c.halfWidth() - xoffset;
  double worldy = c.halfHeight() -yoffset;
  auto pixel = c.transform().inverse() * util::Tuple::point(worldx,worldy,-1);
  auto origin = c.transform().inverse()*util::Tuple::point(0,0,0);
  auto direction = (pixel-origin).normalize();
  return rt::Ray(origin, direction);
}
util::Canvas render(const Camera &c, const World &world)
{
  auto canvas = util::Canvas(c.hsize(),c.vsize());
  for(unsigned y = 0; y < c.vsize(); y++) {
    for(unsigned x = 0; x < c.hsize(); x++) {
      auto ray = rayForPixel(c,x,y);
      auto color = rt::colorAt(world,ray);
      canvas(x,y) = color;
    }
  }
  return canvas;
}
bool isShadowed(const World &world, const util::Tuple &point)
{
  (void)world;
  (void)point;
  auto direction = world.lights()[0].get()->position() - point;
  auto distance = direction.magnitude();
  auto ray = rt::Ray(point,direction.normalization());
  auto intersection = world.intersect(ray);
  if(intersection.hit().has_value() && intersection.hit()->t() < distance) {
    return true;
  }
  return false;
}
util::Color stripeAt(const StripePattern &pattern, const util::Tuple &point)
{
  if(static_cast<int>(std::floor(point.x())) % 2) {
    return pattern.b();
  } else {
    return pattern.a();
  }
}
}

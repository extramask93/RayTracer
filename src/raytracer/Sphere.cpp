//
// Created by damian on 06.07.2020.
//

#include "Sphere.h"
#include <cmath>
rt::Intersection rt::Sphere::intersect(rt::Ray ray)
{
  auto sphereToRay = ray.origin() - util::Tuple::point(0,0,0);
  auto a = ray.direction().dot(ray.direction());
  auto b = 2.0 * ray.direction().dot(sphereToRay);
  auto c = sphereToRay.dot(sphereToRay) -1.0;
  auto discriminant = std::pow(b,2)  - 4 * a * c;
  if(discriminant < 0.0) {
    return rt::Intersection{};
  } else {
    auto t1 = (-b - std::sqrt(discriminant))/(2*a);
    auto t2 = (-b + std::sqrt(discriminant))/(2*a);
    return rt::Intersection{t1,t2};
  }
}
rt::Sphere::Sphere() : Shape()
{

}

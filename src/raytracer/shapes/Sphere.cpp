//
// Created by damian on 06.07.2020.
//

#include "Sphere.h"
#include <intersections/Intersections.h>
#include <cmath>
#include <intersections/Intersection.h>

rt::Intersections rt::Sphere::localIntersect(const Ray &ray)const
{
  //ray = ray.transform(m_transform.inverse());
  auto sphereToRay = ray.origin() - m_origin;
  auto a = ray.direction().dot(ray.direction());
  auto b = 2.0 * ray.direction().dot(sphereToRay);
  auto c = sphereToRay.dot(sphereToRay) -1.0;
  auto discriminant = std::pow(b,2)  - 4 * a * c;
  if(discriminant < 0.0) {
    return Intersections{};
  } else {
    auto t1 = (-b - std::sqrt(discriminant))/(2*a);
    auto t2 = (-b + std::sqrt(discriminant))/(2*a);
    return Intersections { Intersection(t1,this) , Intersection(t2,this)};
  }
}
rt::Sphere::Sphere() : Shape()
{

}
util::Tuple rt::Sphere::localNormalAt(const util::Tuple &point) const
{
  return (point - m_origin);
}
rt::Sphere rt::Sphere::glassSphere()
{
  auto sphere = rt::Sphere();
  sphere.material().setTransparency(1.0).setRefractionIndex(1.5);
  return sphere;
}
rt::AABB rt::Sphere::bounds() const
{
  auto bb = rt::AABB();
  bb.min() = util::Tuple::point(-1,-1,-1);
  bb.max() = util::Tuple::point(1,1,1);
  return bb;
}

//
// Created by damian on 06.07.2020.
//

#include "Sphere.h"
#include <cmath>
#include <Intersection.h>
rt::Intersections rt::Sphere::intersect(rt::Ray ray) const
{
  auto ray2 = ray;
  (void) ray2;
  ray = ray.transform(m_transform.inverse());
  auto sphereToRay = ray.origin() - m_origin;
  auto a = ray.direction().dot(ray.direction());
  auto b = 2.0 * ray.direction().dot(sphereToRay);
  auto c = sphereToRay.dot(sphereToRay) -1.0;
  auto discriminant = std::pow(b,2)  - 4 * a * c;
  if(discriminant < 0.0) {
    return rt::Intersections{};
  } else {
    auto t1 = (-b - std::sqrt(discriminant))/(2*a);
    auto t2 = (-b + std::sqrt(discriminant))/(2*a);
    return rt::Intersections { Intersection(t1,this) , Intersection(t2,this)};
  }
}
rt::Sphere::Sphere() : Shape(), m_transform(util::Matrixd::Identity(4)), m_origin(util::Tuple::point(0,0,0))
{

}
util::Matrixd rt::Sphere::transform() const
{
  return m_transform;
}
void rt::Sphere::setTransform(const util::Matrixd &transorm)
{
  m_transform=transorm;
}
util::Tuple rt::Sphere::normalAt(util::Tuple point) const
{
  auto worldToObjectSpaceTransform = m_transform.inverse();
  auto objectSpacePoint = worldToObjectSpaceTransform * point;
  auto objectNormal = (objectSpacePoint - m_origin);
  auto worldNormal =  m_transform.inverse().transpose()*objectNormal;
  worldNormal.w() = 0;
  return worldNormal.normalize();
}

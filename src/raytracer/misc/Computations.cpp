//
// Created by damian on 10.07.2020.
//

#include "Computations.h"
#include <intersections/Intersections.h>
#include <misc/Shader.h>
namespace rt {
Computations prepareComputations(const Intersection &i, const Ray &ray,const rt::Intersections &intersections){
  (void)intersections;
  Computations comp;
  comp.t = i.t();
  comp.object = i.object();
  comp.point = ray.position(comp.t);
  comp.eyev = -ray.direction();
  comp.normalv = comp.object->normalAt(comp.point,
    intersections.size() > 0 ? intersections.front() : rt::Intersection(0, nullptr));
  comp.inside = false;
  if(comp.normalv.dot(comp.eyev) < 0) {
    comp.inside = true;
    comp.normalv = -comp.normalv;
  }
  comp.reflectv = ray.direction().reflect(comp.normalv);
  comp.overPoint = comp.point + comp.normalv*EPSILON;
  comp.underPoint = comp.point - comp.normalv*EPSILON;
  /*refraction logic*/
  if(intersections.size() > 0 ) {
    std::vector<const Shape *> containers;
    for (const auto &ii : intersections) {
      if (ii == i) {
        if (containers.empty()) {
          comp.n1 = 1.0;
        } else {
          comp.n1 = containers.back()->material().refractionIndex();
        }
      }
      auto obj = std::find_if(containers.begin(), containers.end(), [&](const auto &o) { return o == i.object(); });
      if (obj != containers.end()) {
        containers.erase(obj);
      } else {
        containers.push_back(ii.object());
      }
      if (ii == i) {
        if (containers.empty()) {
          comp.n2 = 1.0;
        } else {
          comp.n2 = containers.back()->material().refractionIndex();
        }
      }
    }
  }
  /******************/
  return comp;
}
util::Color colorAt(const World &world, const Ray &ray, short callsLeft)
{
  auto result = util::Color::BLACK;

  auto intersections = world.intersect(ray);
  if(intersections.hit().has_value()) {
    auto comps = prepareComputations(intersections.hit().value(), ray, intersections);
    result = result + rt::Shader::shadeHit(world, comps, callsLeft);
  }
  return result; //util::Color::BLACK;
}

/*Phong reflection model*/
util::Color lighting(const rt::Material &material,const rt::Shape &object, const rt::PointLight &light,
                         const util::Tuple &position, const util::Tuple &eye, const util::Tuple &normal, bool inShadow)
{

  auto effectiveColor = material.color() * light.intensity();
  if(material.pattern() != nullptr) {
    effectiveColor = rt::patternAtObject(*material.pattern(), object, position);
  }

  //ambient is const
  util::Color ambient = effectiveColor * material.ambient();
  if(inShadow) {
    return ambient;
  }
  auto lightVector = (light.position() - position).normalize();
  auto light_dot_normal = lightVector.dot(normal);//cos(theta)

  util::Color diffuse(0, 0, 0);
  util::Color specular(0, 0, 0);
  if (light_dot_normal < 0) {
    diffuse = util::Color::BLACK;
    specular = util::Color::BLACK;
  } else {
    diffuse = effectiveColor * material.diffuse() * light_dot_normal;
    auto reflectVector = (-lightVector).reflect(normal);
    auto reflect_dot_eye = reflectVector.dot(eye);
    if (reflect_dot_eye <= 0) {
      specular = util::Color::BLACK;
    } else {
      auto factor = std::pow(reflect_dot_eye, material.shininess());
      specular = effectiveColor * material.specular() * factor;
    }
  }
  return ambient + diffuse + specular;
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

util::Color patternAtObject(const Pattern &pattern, const Shape &shape, const util::Tuple &point)
{

  auto pointInObjectSpace = shape.worldToObject(point);//shape.transform().inverse()* point;
  auto pointInPatternSpace = pattern.transform().inverse() * pointInObjectSpace;
  return pattern.patternAt(pointInPatternSpace);
}
util::Color reflectedColor(const World &world, const Computations &comps, short callsLeft)
{
  if(comps.object->material().reflective() ==0 || callsLeft < 1) {
    return util::Color(0,0,0);
  }
  auto reflectedRay = rt::Ray(comps.overPoint, comps.reflectv);
  auto newColor = rt::colorAt(world,reflectedRay,callsLeft-1);
  return newColor * comps.object->material().reflective();
}
util::Color refractedColor(const World &world, const Computations &comps, short callsLeft)
{
  auto transparency = comps.object->material().transparency();
  if(equal(transparency,0.0) || callsLeft < 1){
    return util::Color(0,0,0);
  }
  /*from the definition of Snell's Law*/
  auto ratio = comps.n1 / comps.n2;
  auto cosi = comps.eyev.dot(comps.normalv);
  auto sin2t = std::pow(ratio,2) * (1-std::pow(cosi,2));
  if(sin2t > 1.0) { // critical angle of 90 deg, so we need sint > 1
    return util::Color(0,0,0);
  }
  auto cos_t = sqrt(1.0-sin2t);
  auto d = ratio*cosi- cos_t;
  auto normal = comps.normalv *d;
  auto eyeVector = comps.eyev *ratio;
  auto direction = normal-eyeVector;
  auto refractRay = rt::Ray(comps.underPoint,direction);
  auto color = rt::colorAt(world,refractRay,callsLeft-1) * comps.object->material().transparency();
  return color;
}
double schlick(const Computations &comps)
{
  auto c = comps.eyev.dot(comps.normalv);
  if(comps.n1 > comps.n2) {
    auto n = comps.n1/comps.n2;
    auto sin2t = pow(n,2) * (1.0-pow(c,2));
    if(sin2t > 1.0) {
      return 1.0;
    }
    auto cost = sqrt(1.0-sin2t);
    c = cost;
  }
  auto r0 = pow((comps.n1 - comps.n2) / (comps.n1 + comps.n2),2);
  return r0 + (1.0-r0) * pow(1.0-c,5);
}
bool equal(double x, double y)
{
  return std::fabs(x-y) < std::numeric_limits<double>::epsilon()*EPSILON;
}
std::pair<double, double> spherical_map(const util::Tuple &point)
{
  auto theta = std::atan2(point.x(),point.z());
  auto vec = util::Tuple::vector(point.x(),point.y(),point.z());
  auto radius = vec.magnitude();
  auto phi = acos(point.y() / radius);
  auto raw_u = theta / (2*math::pi<>);
  auto u = 1 - (raw_u + 0.5);
  auto v = 1 - phi / math::pi<>;
  return std::pair<double, double>(u,v);
}
std::pair<double, double> planar_map(const util::Tuple &point)
{
  double u = point.x() - floor(point.x());
  double v = point.z() - floor(point.z());
  return std::make_pair(u,v);
}
}

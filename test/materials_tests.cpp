//
// Created by damian on 08.07.2020.
//
#include <catch2/catch.hpp>
#include <Color.h>
#include <Tuple.h>
#include <materials/Material.h>
#include <lights/PointLight.h>
#include <misc/Computations.h>
#include <shapes/Sphere.h>
#include <patterns/StripePattern.h>
#include <shapes/Plane.h>
SCENARIO("The default material")
{
  GIVEN("Material")
  {
    auto m = rt::Material();
    THEN("")
    {
      REQUIRE(m.color() == util::Color(1, 1, 1));
      REQUIRE(m.ambient() == 0.1);
      REQUIRE(m.diffuse() == 0.9);
      REQUIRE(m.specular() == 0.9);
      REQUIRE(m.shininess() == 200.0);
    }
  }
}
SCENARIO("Shading tests")
{
  GIVEN("Material and position")
  {
    auto m = rt::Material();
    auto position = util::Tuple::point(0, 0, 0);
    auto object = rt::Sphere();
    WHEN("Source of light is behind the eye")
    {
      auto eyev = util::Tuple::vector(0, 0, -1);
      auto normalv = util::Tuple::vector(0, 0, -1);
      auto light = rt::PointLight(util::Tuple::point(0, 0, -10), util::Color(1, 1, 1));
      auto result = rt::lighting(m, object, light, position, eyev, normalv, false);
      THEN("")
      {
        REQUIRE(result == util::Color(1.9, 1.9, 1.9));
      }
    }
    /////////////////////
    WHEN("Lighting with the eye between light and surface, eye offset 45 deg")
    {
      auto eyev = util::Tuple::vector(0, sqrt(2) / 2, sqrt(2) / 2);
      auto normalv = util::Tuple::vector(0, 0, -1);
      auto light = rt::PointLight(util::Tuple::point(0, 0, -10), util::Color(1, 1, 1));
      auto result = rt::lighting(m, object, light, position, eyev, normalv, false);
      THEN("")
      {
        REQUIRE(result == util::Color(1.0, 1.0, 1.0));
      }
    }
    /////////////////////
    WHEN("Lighting with eye opposite surface, light offset 45 deg")
    {
      auto eyev = util::Tuple::vector(0, 0, -1);
      auto normalv = util::Tuple::vector(0, 0, -1);
      auto light = rt::PointLight(util::Tuple::point(0, 10, -10), util::Color(1, 1, 1));
      auto result = rt::lighting(m, object, light, position, eyev, normalv, false);
      THEN("")
      {
        REQUIRE(result == util::Color(0.7364, 0.7364, 0.7364));
      }
    }
    /////////////////////
    WHEN("Lighting with eye in the path of the reflection vector")
    {
      auto eyev = util::Tuple::vector(0, -sqrt(2) / 2, -sqrt(2) / 2);
      auto normalv = util::Tuple::vector(0, 0, -1);
      auto light = rt::PointLight(util::Tuple::point(0, 10, -10), util::Color(1, 1, 1));
      auto result = rt::lighting(m, object, light, position, eyev, normalv, false);
      THEN("")
      {
        REQUIRE(result == util::Color(1.6364, 1.6364, 1.6364));
      }
    }
    /////////////////////
    WHEN("Lighting with the light behind the surface")
    {
      auto eyev = util::Tuple::vector(0, 0, -1);
      auto normalv = util::Tuple::vector(0, 0, -1);
      auto light = rt::PointLight(util::Tuple::point(0, 0, 10), util::Color(1, 1, 1));
      auto result = rt::lighting(m, object, light, position, eyev, normalv, false);
      THEN("")
      {
        REQUIRE(result == util::Color(0.1, 0.1, 0.1));
      }
    }
    WHEN("Lighting with the surface in shadow")
    {
      auto eyev = util::Tuple::vector(0, 0, -1);
      auto normalv = util::Tuple::vector(0, 0, -1);
      auto light = rt::PointLight(util::Tuple::point(0, 0, -10), util::Color(1, 1, 1));
      auto result = rt::lighting(m, object, light, position, eyev, normalv, true);
      THEN("")
      {
        REQUIRE(result == util::Color(0.1, 0.1, 0.1));
      }
    }

    WHEN("Lighting with a pattern applied")
    {
      m.setAmbient(1).setDiffuse(0).setSpecular(0).setPattern(
        std::make_unique<rt::StripePattern>(util::Color(1, 1, 1), util::Color(0, 0, 0)));
      auto eyev = util::Tuple::vector(0, 0, -1);
      auto normalv = util::Tuple::vector(0, 0, -1);
      auto light = rt::PointLight(util::Tuple::point(0, 0, -10), util::Color(1, 1, 1));
      auto c1 = rt::lighting(m, object, light, util::Tuple::point(0.9, 0, 0), eyev, normalv, false);
      auto c2 = rt::lighting(m, object, light, util::Tuple::point(1.1, 0, 0), eyev, normalv, false);
      THEN("")
      {
        REQUIRE(c1 == util::Color(1, 1, 1));
        REQUIRE(c2 == util::Color(0, 0, 0));
      }
    }
  }
}
SCENARIO("Reflectivity fo the deffault material")
{
  GIVEN("")
  {
    auto m = rt::Material();
    THEN("")
    {
      REQUIRE(m.reflective() == 0);
    }
  }
}

SCENARIO("Precomputing the reflection vector")
{
  GIVEN("")
  {
    auto shape = rt::Plane();
    auto r = rt::Ray(util::Tuple::point(0,1,-1), util::Tuple::vector(0, -std::sqrt(2)/2, std::sqrt(2)/2));
    auto i = rt::Intersection(std::sqrt(2),&shape);
    auto comps = rt::prepareComputations(i,r);
    THEN("")
    {
      REQUIRE(comps.reflectv == util::Tuple::vector(0, std::sqrt(2)/2, std::sqrt(2)/2));
    }
  }
}

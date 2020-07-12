//
// Created by damian on 07.07.2020.
//
#include <catch2/catch.hpp>
#include <Tuple.h>
#include <Matrix.h>
#include <shapes/Sphere.h>
#include <intersections/Intersection.h>
#include <intersections/Intersections.h>
#include <misc/Computations.h>

SCENARIO("An intersection encapsulates t and object")
{
  GIVEN("A sphere")
  {
    auto s = rt::Sphere();
    WHEN("There is an intersection")
    {
      auto i = rt::Intersection(3.5, &s);
      THEN("")
      {
        REQUIRE(i.t() == 3.5);
        REQUIRE(i.object() == &s);
      }
    }
  }
}
SCENARIO("Aggregating intersections")
{
  GIVEN("A sphere")
  {
    auto sphere = rt::Sphere();
    AND_GIVEN("intersections")
    {
      auto i1 = rt::Intersection(1, &sphere);
      auto i2 = rt::Intersection(2, &sphere);
      WHEN("Creating container")
      {
        auto xs = rt::Intersections{ i1, i2 };
        THEN("")
        {
          REQUIRE(xs.size() == 2);
          REQUIRE(xs[0].t() == 1);
          REQUIRE(xs[1].t() == 2);
        }
      }
    }
  }
}
SCENARIO("The hit, when all intersections have positive t")
{
  GIVEN("A spehre")
  {
    auto s = rt::Sphere();
    AND_GIVEN("Itersections")
    {
      auto i1 = rt::Intersection(1, &s);
      auto i2 = rt::Intersection(2, &s);
      auto xs = rt::Intersections{ i1, i2 };
      WHEN("Hits")
      {
        auto i = xs.hit();
        THEN("")
        {
          REQUIRE(i == i1);
        }
      }
    }
  }
}
SCENARIO("The hit, when some intersections have negative t")
{
  GIVEN("A spehre")
  {
    auto s = rt::Sphere();
    AND_GIVEN("Itersections")
    {
      auto i1 = rt::Intersection(-1, &s);
      auto i2 = rt::Intersection(1, &s);
      auto xs = rt::Intersections{ i1, i2 };
      WHEN("Hits")
      {
        auto i = xs.hit();
        THEN("")
        {
          REQUIRE(i == i2);
        }
      }
    }
  }
}

SCENARIO("The hit, when all intersections have negative t")
{
  GIVEN("A spehre")
  {
    auto s = rt::Sphere();
    AND_GIVEN("Itersections")
    {
      auto i1 = rt::Intersection(-2, &s);
      auto i2 = rt::Intersection(-1, &s);
      auto xs = rt::Intersections{ i1, i2 };
      WHEN("Hits")
      {
        auto i = xs.hit();
        THEN("")
        {
          REQUIRE(i.has_value() == false);
        }
      }
    }
  }
}

SCENARIO("The hit is always the lowest nonnegtive intersection")
{
  GIVEN("A spehre")
  {
    auto s = rt::Sphere();
    AND_GIVEN("Itersections")
    {
      auto i1 = rt::Intersection(5, &s);
      auto i2 = rt::Intersection(7, &s);
      auto i3 = rt::Intersection(-3, &s);
      auto i4 = rt::Intersection(2, &s);
      auto xs = rt::Intersections{ i1, i2, i3, i4 };
      WHEN("Hits")
      {
        auto i = xs.hit();
        THEN("")
        {
          REQUIRE(i == i4);
        }
      }
    }
  }
}
SCENARIO("Precomputing the state of an intersection")
{
  GIVEN("A ray, sphere, intersection")
  {
    auto r = rt::Ray(util::Tuple::point(0, 0, -5), util::Tuple::vector(0, 0, 1));
    auto shape = rt::Sphere();
    auto i = rt::Intersection(4, &shape);
    WHEN("")
    {
      auto comps = rt::prepareComputations(i, r);
      THEN("")
      {
        REQUIRE(comps.t == i.t());
        REQUIRE(comps.object == i.object());
        REQUIRE(comps.point == util::Tuple::point(0, 0, -1));
        REQUIRE(comps.eyev == util::Tuple::vector(0, 0, -1));
        REQUIRE(comps.normalv == util::Tuple::vector(0, 0, -1));
      }
    }
  }
}
SCENARIO("The hit when an intersection occurs on the outside")
{
  GIVEN("Ray, sphere and intersection")
  {
    auto r = rt::Ray(util::Tuple::point(0, 0, -5), util::Tuple::vector(0, 0, 1));
    auto shape = rt::Sphere();
    auto i = rt::Intersection(4, &shape);
    WHEN("")
    {
      auto comps = rt::prepareComputations(i, r);
      THEN("")
      {
        REQUIRE(comps.inside == false);
      }
    }
  }
}
SCENARIO("The hit when an intersection occurs on the inside")
{
  GIVEN("Ray, sphere and intersection")
  {
    auto r = rt::Ray(util::Tuple::point(0, 0, 0), util::Tuple::vector(0, 0, 1));
    auto shape = rt::Sphere();
    auto i = rt::Intersection(1, &shape);
    WHEN("")
    {
      auto comps = rt::prepareComputations(i, r);
      THEN("")
      {
        REQUIRE(comps.point == util::Tuple::point(0,0,1));
        REQUIRE(comps.eyev == util::Tuple::vector(0,0,-1));
        REQUIRE(comps.inside == true);
        REQUIRE(comps.normalv == util::Tuple::vector(0,0,-1));
      }
    }
  }
}
SCENARIO("The hit should offset the point")
{
  GIVEN("Ray, sphere and intersection")
  {
    auto r = rt::Ray(util::Tuple::point(0, 0, -5), util::Tuple::vector(0, 0, 1));
    auto shape = rt::Sphere();
    shape.setTransform(util::Matrixd::translation(0,0,1));
    auto i = rt::Intersection(5, &shape);
    WHEN("")
    {
      auto comps = rt::prepareComputations(i, r);
      THEN("")
      {
        REQUIRE(comps.overPoint.z() < -EPSILON / 2);
        REQUIRE(comps.point.z() >  comps.overPoint.z());
      }
    }
  }
}

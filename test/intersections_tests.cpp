//
// Created by damian on 07.07.2020.
//
#include <catch2/catch.hpp>
#include <Tuple.h>
#include <Matrix.h>
#include <shapes/Sphere.h>
#include <shapes/Triangle.h>
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
        REQUIRE(comps.point == util::Tuple::point(0, 0, 1));
        REQUIRE(comps.eyev == util::Tuple::vector(0, 0, -1));
        REQUIRE(comps.inside == true);
        REQUIRE(comps.normalv == util::Tuple::vector(0, 0, -1));
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
    shape.setTransform(util::Matrixd::translation(0, 0, 1));
    auto i = rt::Intersection(5, &shape);
    WHEN("")
    {
      auto comps = rt::prepareComputations(i, r);
      THEN("")
      {
        REQUIRE(comps.overPoint.z() < -EPSILON / 2);
        REQUIRE(comps.point.z() > comps.overPoint.z());
      }
    }
  }
}

SCENARIO("Finding n1 and n2 at various intersections")
{
  GIVEN("Ray, sphere and intersection")
  {
    std::vector<std::tuple<int, double, double>> indexes{
      { 0, 1.0, 1.5 },
      { 1, 1.5, 2.0 },
      { 2, 2.0, 2.5 },
      { 3, 2.5, 2.5 },
      { 4, 2.5, 1.5 },
      { 5, 1.5, 1.0 }
    };
    auto A = rt::Sphere::glassSphere();
    A.transform() = util::Matrixd::scaling(2, 2, 2);
    A.material().setRefractionIndex(1.5);
    auto B = rt::Sphere::glassSphere();
    B.transform() = util::Matrixd::translation(0, 0, -0.25);
    B.material().setRefractionIndex(2.0);
    auto C = rt::Sphere::glassSphere();
    C.transform() = util::Matrixd::translation(0, 0, 0.25);
    C.material().setRefractionIndex(2.5);
    auto r = rt::Ray(util::Tuple::point(0, 0, -4), util::Tuple::vector(0, 0, 1));
    auto xs = rt::Intersections{ rt::Intersection(2, &A), rt::Intersection(2.75, &B), rt::Intersection(3.25,&C), rt::Intersection(4.75, &B), rt::Intersection(5.25, &C), rt::Intersection(5.25, &C), rt::Intersection(6, &A) };
    WHEN("")
    {
      for (unsigned idx = 0; const auto i : xs) {
        auto comps = rt::prepareComputations(i, r,xs);
        THEN("")
        {
          REQUIRE(comps.n1 == std::get<1>(indexes[idx]));
          REQUIRE(comps.n2 == std::get<2>(indexes[idx++]));
        }
      }
    }
  }
}
SCENARIO("The under point is offset below the surface") {
  GIVEN(""){
    auto ray = rt::Ray(util::Tuple::point(0,0,-5),util::Tuple::vector(0,0,1));
    auto shape = rt::Sphere::glassSphere();
    shape.transform() = util::Matrixd::translation(0,0,1);
    auto i = rt::Intersection(5,&shape);
    auto xs = rt::Intersections{i};
    auto comps = rt::prepareComputations(i,ray,xs);
    THEN("") {
      REQUIRE(comps.underPoint.z() > EPSILON/2);
      REQUIRE(comps.point.z() < comps.underPoint.z());
    }
  }
}
SCENARIO("The Schlick approximation under total internal reflection") {
  GIVEN("") {
    auto shape = rt::Sphere::glassSphere();
    auto ray = rt::Ray(util::Tuple::point(0,0,sqrt(2)/2), util::Tuple::vector(0,1,0));
    auto xs = rt::Intersections{rt::Intersection(-sqrt(2)/2,&shape), rt::Intersection(sqrt(2)/2,&shape)};
    auto comps = rt::prepareComputations(xs[1], ray, xs);
    auto reflectance = rt::schlick(comps);
    THEN("") {
      REQUIRE(reflectance == 1.0);
    }
  }
}

SCENARIO("The Schlick approximation with a perpendicular viewing angle") {
  GIVEN("") {
    auto shape = rt::Sphere::glassSphere();
    auto ray = rt::Ray(util::Tuple::point(0,0,0), util::Tuple::vector(0,1,0));
    auto xs = rt::Intersections{rt::Intersection(-1,&shape), rt::Intersection(1,&shape)};
    auto comps = rt::prepareComputations(xs[1], ray, xs);
    auto reflectance = rt::schlick(comps);
    THEN("") {
      REQUIRE(reflectance == Approx(0.04));
    }
  }
}

SCENARIO("The Schlick approximation with a small angle and n2 > n1") {
  GIVEN("") {
    auto shape = rt::Sphere::glassSphere();
    auto ray = rt::Ray(util::Tuple::point(0,0.99,-2), util::Tuple::vector(0,0,1));
    auto xs = rt::Intersections{rt::Intersection(1.8589,&shape)};
    auto comps = rt::prepareComputations(xs[0], ray, xs);
    auto reflectance = rt::schlick(comps);
    THEN("") {
      REQUIRE(reflectance == Approx(0.48873));
    }
  }
}
SCENARIO("An intersection can encapsulate u and v") {
  GIVEN("") {
    auto s = std::make_shared<rt::Triangle>(util::Tuple::point(0,1,0),
      util::Tuple::point(-1,0,0), util::Tuple::point(1,0,0));
    WHEN("")
    {
      auto i = rt::Intersection(3.5,s.get(),0.2,0.4);
      THEN("") {
        REQUIRE(i.u() == 0.2);
        REQUIRE(i.v() == 0.4);
      }
    }
  }
}
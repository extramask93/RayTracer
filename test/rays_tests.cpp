//
// Created by damian on 06.07.2020.
//
#include <catch2/catch.hpp>
#include <Tuple.h>
#include <Matrix.h>
#include <ray/Ray.h>
SCENARIO("Creating and querying a ray")
{
  GIVEN("origin and direction")
  {
    auto origin = util::Tuple::point(1, 2, 3);
    auto direction = util::Tuple::vector(4, 5, 6);
    WHEN("Creaing a ray")
    {
      auto ray = rt::Ray(origin, direction);
      THEN("Properties are correctly set")
      {
        REQUIRE(ray.origin() == origin);
        REQUIRE(ray.direction() == direction);
      }
    }
  }
}
SCENARIO("Computing a point from a distance")
{
  GIVEN("A ray")
  {
    auto origin = util::Tuple::point(2, 3, 4);
    auto direction = util::Tuple::vector(1, 0, 0);
    auto ray = rt::Ray(origin, direction);
    THEN("")
    {
      REQUIRE(ray.position(0) == util::Tuple::point(2,3,4));
    }
    AND_THEN("") {
      REQUIRE(ray.position(1) == util::Tuple::point(3,3,4));
    }
    AND_THEN("") {
      REQUIRE(ray.position(-1) == util::Tuple::point(1,3,4));
    }
    AND_THEN("") {
      REQUIRE(ray.position(2.5) == util::Tuple::point(4.5,3,4));
    }
  }
}
SCENARIO("Translating a ray") {
  GIVEN("A ray") {
    auto r = rt::Ray(util::Tuple::point(1,2,3), util::Tuple::vector(0,1,0));
    auto m = util::Matrixd::translation(3,4,5);
    WHEN("transforming") {
      auto r2 = r.transform(m);
      THEN("") {
        REQUIRE(r2.origin() == util::Tuple::point(4,6,8));
        REQUIRE(r2.direction() == util::Tuple::vector(0,1,0));
      }
    }
  }
}
SCENARIO("Scaling a ray") {
  GIVEN("A ray") {
    auto r = rt::Ray(util::Tuple::point(1,2,3), util::Tuple::vector(0,1,0));
    auto m = util::Matrixd::scaling(2,3,4);
    WHEN("transforming") {
      auto r2 = r.transform(m);
      THEN("") {
        REQUIRE(r2.origin() == util::Tuple::point(2,6,12));
        REQUIRE(r2.direction() == util::Tuple::vector(0,3,0));
      }
    }
  }
}

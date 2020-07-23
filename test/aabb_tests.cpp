//
// Created by damian on 23.07.2020.
//

#include <catch2/catch.hpp>
#include <Tuple.h>
#include <misc/AABB.h>
#include <shapes/Sphere.h>
#include <shapes/Plane.h>
#include <shapes/Cube.h>
#include <shapes/Cylinder.h>

SCENARIO("Creating a bounding box")
{
  GIVEN("")
  {
    auto aabb = rt::AABB(util::Tuple::point(-1, -1, -1), util::Tuple::point(1, 1, 1));
    THEN("")
    {
      REQUIRE(aabb.min() == util::Tuple::point(-1, -1, -1));
      REQUIRE(aabb.max() == util::Tuple::point(1, 1, 1));
    }
  }
}
SCENARIO("Creating empty bounding box") {
  GIVEN("") {
    auto aabb = rt::AABB();
    WHEN("AABB is not modified") {
      THEN("") {
        REQUIRE(aabb.max().x() == Approx(math::ninf<>));
        REQUIRE(aabb.max().y() == Approx(math::ninf<>));
        REQUIRE(aabb.max().z() == Approx(math::ninf<>));
        REQUIRE(aabb.min().x() == Approx(math::inf<>));
        REQUIRE(aabb.min().y() == Approx(math::inf<>));
        REQUIRE(aabb.min().z() == Approx(math::inf<>));
      }
    }
  }
}
SCENARIO("Expanding empty bounding box") {
  GIVEN("") {
    auto aabb = rt::AABB();
    WHEN("Adding points") {
      aabb.add(util::Tuple::point(2,2,2));
      aabb.add(util::Tuple::point(-2,-2,-2));
      THEN("") {
        REQUIRE(aabb.max() == util::Tuple::point(2,2,2));
        REQUIRE(aabb.min() == util::Tuple::point(-2,-2,-2));
      }
    }
  }
}
SCENARIO("Shape return it's bounding box") {
  GIVEN("") {
    auto sphere = rt::Sphere();
    auto result = rt::AABB(util::Tuple::point(-1,-1,-1), util::Tuple::point(1,1,1));
    auto aabb = sphere.bounds();
    THEN("") {
      REQUIRE(aabb == result);
    }
  }
}
SCENARIO("Plane return it's bounding box") {
  GIVEN("") {
    auto sphere = rt::Plane();
    auto result = rt::AABB(
      util::Tuple::point(math::ninf<>,0,math::ninf<>),
      util::Tuple::point(math::inf<>,0,math::inf<>));
    auto aabb = sphere.bounds();
    THEN("") {
      REQUIRE(aabb.max() == result.max());
    }
  }
}

SCENARIO("Cube return it's bounding box") {
  GIVEN("") {
    auto sphere = rt::Cube();
    auto result = rt::AABB(
      util::Tuple::point(-1,-1,-1),
      util::Tuple::point(1,1,1));
    auto aabb = sphere.bounds();
    THEN("") {
      REQUIRE(aabb.max() == result.max());
    }
  }
}

SCENARIO("boundless cylinder return it's bounding box") {
  GIVEN("") {
    auto sphere = rt::Cylinder();
    auto result = rt::AABB(
      util::Tuple::point(-1,math::ninf<>,-1),
      util::Tuple::point(1,math::inf<>,1));
    auto aabb = sphere.bounds();
    THEN("") {
      REQUIRE(aabb == result);
    }
  }
}

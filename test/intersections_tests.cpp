//
// Created by damian on 07.07.2020.
//
#include <catch2/catch.hpp>
#include <Tuple.h>
#include <Matrix.h>
#include <shapes/Sphere.h>
#include <Intersection.h>

SCENARIO("An intersection encapsulates t and object") {
GIVEN("A sphere") {
  auto s = rt::Sphere();
  WHEN("There is an intersection") {
    auto i = rt::Intersection(3.5,s);
    THEN("") {
      REQUIRE(i.t() == 3.5);
      REQUIRE(i.object() == s);
    }
  }
}
}
SCENARIO("Aggregating intersections") {
  GIVEN("A sphere") {
    auto sphere = rt::Sphere();
    AND_GIVEN("intersections") {
      auto i1 = rt::Intersection(1,sphere);
      auto i2 = rt::Intersection(2,sphere);
      WHEN("Creating container") {
        auto xs = rt::Intersections{i1,i2};
        THEN("") {
          REQUIRE(xs.size() ==2);
          REQUIRE(xs[0].t() == 1);
          REQUIRE(xs[1].t() == 2);
        }
      }
    }
  }
}

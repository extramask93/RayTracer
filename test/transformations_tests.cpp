//
// Created by damian on 11.07.2020.
//
#include <catch2/catch.hpp>
#include <Tuple.h>
#include <Matrix.h>
#include <misc/Computations.h>
SCENARIO("The transformation matrix for the default orientation") {
  GIVEN("") {
    auto from = util::Tuple::point(0,0,0);
    auto to = util::Tuple::point(0,0,-1);
    auto up = util::Tuple::vector(0,1,0);
    WHEN("") {
      auto t = rt::viewTransformation(from,to,up);
      THEN("") {
        REQUIRE(t == util::Matrixd::Identity(4));
      }
    }
  }
}
SCENARIO("A view transformation matrix looking in positive z direction") {
  GIVEN("") {
    auto from = util::Tuple::point(0,0,0);
    auto to = util::Tuple::point(0,0,1);
    auto up = util::Tuple::vector(0,1,0);
    WHEN("") {
      auto t = rt::viewTransformation(from,to,up);
      THEN("") {
        REQUIRE(t == util::Matrixd::scaling(-1,1,-1));
      }
    }
  }
}
SCENARIO("The view transformation moves the world") {
  GIVEN("") {
    auto from = util::Tuple::point(0,0,8);
    auto to = util::Tuple::point(0,0,0);
    auto up = util::Tuple::vector(0,1,0);
    WHEN("") {
      auto t = rt::viewTransformation(from,to,up);
      THEN("") {
        REQUIRE(t == util::Matrixd::translation(0,0,-8));
      }
    }
  }
}
SCENARIO("An arbitrary view transformation") {
  GIVEN("") {
    auto from = util::Tuple::point(1,3,2);
    auto to = util::Tuple::point(4,-2,8);
    auto up = util::Tuple::vector(1,1,0);
    WHEN("") {
      auto t = rt::viewTransformation(from,to,up);
      auto expected = util::Matrixd(4,4);
      expected << -0.50709, 0.50709, 0.67612, -2.36643,
                   0.76772, 0.60609, 0.12122, -2.82843,
                  -0.35857, 0.59761, -0.71714, 0.00000,
                   0.00000, 0.00000, 0.00000, 1.00000;
      THEN("") {
        REQUIRE(t == expected);
      }
    }
  }
}

//
// Created by damian on 20.07.2020.
//
#include <catch2/catch.hpp>
#include <vector>
#include <tuple>
#include <Tuple.h>
#include <shapes/Cube.h>
#include <intersections/Intersections.h>
SCENARIO("A ray intersects a cube") {
  GIVEN("") {
    std::vector<std::tuple<util::Tuple,util::Tuple,double,double>> cases{
      {util::Tuple::point(5,0.5,0),util::Tuple::vector(-1,0,0),4,6},
      {util::Tuple::point(-5,0.5,0),util::Tuple::vector(1,0,0),4,6},
      {util::Tuple::point(0.5,5,0),util::Tuple::vector(0,-1,0),4,6},
      {util::Tuple::point(0.5,-5,0),util::Tuple::vector(0,1,0),4,6},
      {util::Tuple::point(0.5,0,5),util::Tuple::vector(0,0,-1),4,6},
      {util::Tuple::point(0.5,0,-5),util::Tuple::vector(0,0,1),4,6},
      {util::Tuple::point(0,0.5,0),util::Tuple::vector(0,0,1),-1,1},
    };
    auto c = rt::Cube();
    for (const auto &loc : cases) {
      auto r = rt::Ray(std::get<0>(loc), std::get<1>(loc));
      auto xs = c.localIntersect(r);
      THEN("") {
        REQUIRE(xs.size() == 2);
        REQUIRE(xs[0].t() == std::get<2>(loc));
        REQUIRE(xs[1].t() == std::get<3>(loc));
      }
    }
  }
}

SCENARIO("the normal on the surface of a cube") {
  GIVEN("") {
    std::vector<std::tuple<util::Tuple,util::Tuple>> cases{
      {util::Tuple::point(1,0.5,-0.8),util::Tuple::vector(1,0,0)},
      {util::Tuple::point(-1,-0.2,0.9),util::Tuple::vector(-1,0,0)},
      {util::Tuple::point(0.4,1,-0.1),util::Tuple::vector(0,1,0)},
      {util::Tuple::point(0.3,-1,-0.7),util::Tuple::vector(0,-1,0)},
      {util::Tuple::point(-0.6,0.3,1),util::Tuple::vector(0,0,1)},
      {util::Tuple::point(0.4,0.4,-1),util::Tuple::vector(0,0,-1)},
      {util::Tuple::point(1,1,1),util::Tuple::vector(1,0,0)},
      {util::Tuple::point(-1,-1,-1),util::Tuple::vector(-1,0,0)},
    };
    auto c = rt::Cube();
    for (const auto &loc : cases) {
      auto p = std::get<0>(loc);
      auto normal  = c.localNormalAt(p, rt::Intersection(0, nullptr));
      THEN("") {
        REQUIRE(normal == std::get<1>(loc));
      }
    }
  }
}

//
// Created by damian on 28.07.2020.
//
#include <catch2/catch.hpp>
#include <shapes/SmoothTriangle.h>
#include <intersections/Intersections.h>
#include <misc/Computations.h>
#include <Tuple.h>
SCENARIO("Constructing a a smooth triangle") {
  GIVEN("") {
    auto p1 = util::Tuple::point(0,1,0);
    auto p2 = util::Tuple::point(-1,0,0);
    auto p3 = util::Tuple::point(1,0,0);
    auto n1 = util::Tuple::vector(0,1,0);
    auto n2 = util::Tuple::vector(-1,0,0);
    auto n3 = util::Tuple::vector(1,0,0);
    WHEN("") {
      auto tri = rt::SmoothTriangle(p1,p2,p3,n1,n2,n3);
      THEN("") {
        REQUIRE(tri.p1() == p1);
        REQUIRE(tri.p2() == p2);
        REQUIRE(tri.p3() == p3);
        REQUIRE(tri.n1() == n1);
        REQUIRE(tri.n2() == n2);
        REQUIRE(tri.n3() == n3);
      }
    }
  }
}
SCENARIO("An intersection with a smooth triangle stores u and v") {
  GIVEN("") {
    auto p1 = util::Tuple::point(0,1,0);
    auto p2 = util::Tuple::point(-1,0,0);
    auto p3 = util::Tuple::point(1,0,0);
    auto n1 = util::Tuple::vector(0,1,0);
    auto n2 = util::Tuple::vector(-1,0,0);
    auto n3 = util::Tuple::vector(1,0,0);
    WHEN("") {
      auto tri = rt::SmoothTriangle(p1,p2,p3,n1,n2,n3);
      auto r = rt::Ray(util::Tuple::point(-0.2,0.3,-2), util::Tuple::vector(0,0,1));
      auto xs = tri.localIntersect(r);
      THEN("") {
        REQUIRE(xs[0].u() == Approx(0.45));
        REQUIRE(xs[0].v() == Approx(0.25));
      }
    }
  }
}
SCENARIO("A smoth triangle uses u and v to interpolate the normal") {
  GIVEN("") {
    auto p1 = util::Tuple::point(0,1,0);
    auto p2 = util::Tuple::point(-1,0,0);
    auto p3 = util::Tuple::point(1,0,0);
    auto n1 = util::Tuple::vector(0,1,0);
    auto n2 = util::Tuple::vector(-1,0,0);
    auto n3 = util::Tuple::vector(1,0,0);
    WHEN("") {
      auto tri = rt::SmoothTriangle(p1,p2,p3,n1,n2,n3);
      auto i = rt::Intersection(1,&tri,0.45,0.25);
      auto n = tri.normalAt(util::Tuple::point(0, 0, 0), i);
      THEN("") {
        REQUIRE(n == util::Tuple::vector(-0.5547,0.83205,0));
      }
    }
  }
}

SCENARIO("Preparing the normal on a smooth triangle") {
  GIVEN("") {
    auto p1 = util::Tuple::point(0,1,0);
    auto p2 = util::Tuple::point(-1,0,0);
    auto p3 = util::Tuple::point(1,0,0);
    auto n1 = util::Tuple::vector(0,1,0);
    auto n2 = util::Tuple::vector(-1,0,0);
    auto n3 = util::Tuple::vector(1,0,0);
    WHEN("") {
      auto tri = rt::SmoothTriangle(p1,p2,p3,n1,n2,n3);
      auto i = rt::Intersection(1,&tri,0.45,0.25);
      auto r = rt::Ray(util::Tuple::point(-0.2,0.3,-2), util::Tuple::vector(0,0,1));
      auto xs =  rt::Intersections{i};
      auto coms = rt::prepareComputations(i,r,xs);
      THEN("") {
        REQUIRE(coms.normalv == util::Tuple::vector(-0.5547,0.83205,0));
      }
    }
  }
}

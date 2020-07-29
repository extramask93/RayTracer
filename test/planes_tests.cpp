//
// Created by damian on 12.07.2020.
//
#include <catch2/catch.hpp>
#include <Tuple.h>
#include <shapes/Plane.h>
SCENARIO("The normal of a plane is constat everywhere") {
  GIVEN("") {
    auto p = rt::Plane();
    WHEN("") {
      auto n1 = p.localNormalAt(util::Tuple::point(0, 0, 0), rt::Intersection(0, nullptr));
      auto n2 = p.localNormalAt(util::Tuple::point(10, 0, -10), rt::Intersection(0, nullptr));
      auto n3 = p.localNormalAt(util::Tuple::point(-5, 0, 150), rt::Intersection(0, nullptr));
      THEN("") {
        REQUIRE(n1 == util::Tuple::vector(0,1,0));
        REQUIRE(n2 == util::Tuple::vector(0,1,0));
        REQUIRE(n3 == util::Tuple::vector(0,1,0));
      }
    }
  }
}
SCENARIO("Intersect with a ray parallel to the plane") {
  GIVEN("") {
    auto p = rt::Plane();
    auto r = rt::Ray(util::Tuple::point(0,10,0),util::Tuple::vector(0,0,1));
    WHEN("") {
      auto xs = p.localIntersect(r);
      THEN("") {
        REQUIRE(xs.hit().has_value() == false);
      }
    }
  }
}

SCENARIO("Intersect with coplanar ray") {
  GIVEN("") {
    auto p = rt::Plane();
    auto r = rt::Ray(util::Tuple::point(0,0,0),util::Tuple::vector(0,0,1));
    WHEN("") {
      auto xs = p.localIntersect(r);
      THEN("") {
        REQUIRE(xs.hit().has_value() == false);
      }
    }
  }
}

SCENARIO("A ray intersecting plane from above") {
  GIVEN("") {
    auto p = rt::Plane();
    auto r = rt::Ray(util::Tuple::point(0,1,0),util::Tuple::vector(0,-1,0));
    WHEN("") {
      auto xs = p.localIntersect(r);
      THEN("") {
        REQUIRE(xs.hit().has_value() == true);
        REQUIRE(xs.size() == 1);
        REQUIRE(xs[0].t() == 1);
        REQUIRE(*xs[0].object() == p);
      }
    }
  }
}


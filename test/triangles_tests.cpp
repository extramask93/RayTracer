//
// Created by damian on 25.07.2020.
//
#include <catch2/catch.hpp>
#include <shapes/Shape.h>
#include <shapes/Triangle.h>
#include <intersections/Intersections.h>

SCENARIO("Constructing a triangle") {
  GIVEN("") {
    auto p1 = util::Tuple::point(0,1,0);
    auto p2 = util::Tuple::point(-1,0,0);
    auto p3 = util::Tuple::point(1,0,0);
    auto t = std::make_shared<rt::Triangle>(p1,p2,p3);
    THEN("") {
      REQUIRE(t->p1() == p1);
      REQUIRE(t->p2() == p2);
      REQUIRE(t->p3() == p3);
      REQUIRE(t->e1() == util::Tuple::vector(-1,-1,0));
      REQUIRE(t->e2() == util::Tuple::vector(1,-1,0));
      REQUIRE(t->normal() == util::Tuple::vector(0,0,-1));
    }
  }
}
SCENARIO("Finding the normal on a triangle") {
  GIVEN("") {
    auto t = std::make_shared<rt::Triangle>(util::Tuple::point(0,1,0), util::Tuple::point(-1,0,0), util::Tuple::point(1,0,0));
    WHEN("") {
      auto n1 = t->localNormalAt(util::Tuple::point(0,0.5,0));
      auto n2 = t->localNormalAt(util::Tuple::point(-0.5,0.75,0));
      auto n3 = t->localNormalAt(util::Tuple::point(0.5,0.25,0));
      THEN("") {
        REQUIRE(n1 == t->normal());
        REQUIRE(n2 == t->normal());
        REQUIRE(n3 == t->normal());
      }
    }
  }
}
SCENARIO("Intersecting a ray parallel to the triangle") {
  GIVEN("") {
    auto t = std::make_shared<rt::Triangle>(util::Tuple::point(0,1,0), util::Tuple::point(-1,0,0), util::Tuple::point(1,0,0));
    auto r = rt::Ray(util::Tuple::point(0,-1,-2), util::Tuple::vector(0,1,0));
    WHEN("") {
      auto xs = t->localIntersect(r);
      THEN("") {
        REQUIRE(xs.size() == 0);
      }
    }
  }
}
SCENARIO("A ray misses the p1-p3 edge") {
  GIVEN("") {
    auto t = std::make_shared<rt::Triangle>(util::Tuple::point(0,1,0), util::Tuple::point(-1,0,0), util::Tuple::point(1,0,0));
    auto r = rt::Ray(util::Tuple::point(1,1,-2), util::Tuple::vector(0,0,1));
    WHEN("") {
      auto xs = t->localIntersect(r);
      THEN("") {
        REQUIRE(xs.size() == 0);
      }
    }
  }
}

SCENARIO("A ray misses the p1-p2 edge") {
  GIVEN("") {
    auto t = std::make_shared<rt::Triangle>(util::Tuple::point(0,1,0), util::Tuple::point(-1,0,0), util::Tuple::point(1,0,0));
    auto r = rt::Ray(util::Tuple::point(-1,1,-2), util::Tuple::vector(0,0,1));
    WHEN("") {
      auto xs = t->localIntersect(r);
      THEN("") {
        REQUIRE(xs.size() == 0);
      }
    }
  }
}

SCENARIO("A ray misses the p2-p3 edge") {
  GIVEN("") {
    auto t = std::make_shared<rt::Triangle>(util::Tuple::point(0,1,0), util::Tuple::point(-1,0,0), util::Tuple::point(1,0,0));
    auto r = rt::Ray(util::Tuple::point(0,-1,-2), util::Tuple::vector(0,0,1));
    WHEN("") {
      auto xs = t->localIntersect(r);
      THEN("") {
        REQUIRE(xs.size() == 0);
      }
    }
  }
}

SCENARIO("A ray strikes a trieangle") {
  GIVEN("") {
    auto t = std::make_shared<rt::Triangle>(util::Tuple::point(0,1,0), util::Tuple::point(-1,0,0), util::Tuple::point(1,0,0));
    auto r = rt::Ray(util::Tuple::point(0,0.5,-2), util::Tuple::vector(0,0,1));
    WHEN("") {
      auto xs = t->localIntersect(r);
      THEN("") {
        REQUIRE(xs.size() == 1);
        REQUIRE(xs[0].t() == 2);
      }
    }
  }
}

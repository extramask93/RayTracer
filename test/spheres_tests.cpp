//
// Created by damian on 06.07.2020.
//
#include <catch2/catch.hpp>
#include <Ray.h>
#include <Sphere.h>
SCENARIO("A ray intersects a sphere at two points") {
  GIVEN("a ray") {
    auto ray = rt::Ray(util::Tuple::point(0,0,-5),util::Tuple::vector(0,0,1));
    AND_GIVEN("a sphere") {
      auto sphere = rt::Sphere();
      WHEN("ray intersects sphere") {
        auto xs = sphere.intersect(ray);
        THEN("There are to intersection points") {
          REQUIRE(xs.count() == 2);
          AND_THEN("Those points lay x units away from origin") {
            REQUIRE(xs[0] == 4.0);
            REQUIRE(xs[1] == 6.0);
          }
        }
      }
    }
  }
}
SCENARIO("A ray intersects sphere at a tangent") {
  GIVEN("A ray") {
    auto ray = rt::Ray(util::Tuple::point(0,1,-5),util::Tuple::vector(0,0,1));
    AND_GIVEN("A sphere") {
      auto s = rt::Sphere();
      WHEN("Intersecting") {
        auto xs = s.intersect(ray);
        THEN("") {
          REQUIRE(xs.count() == 2);
          REQUIRE(xs[0] == 5.0);
          REQUIRE(xs[1] == 5.0);
        }
      }
    }
  }
}
SCENARIO("A ray misses a sphere") {
  GIVEN("A ray") {
    auto ray = rt::Ray(util::Tuple::point(0,2,-5),util::Tuple::vector(0,0,1));
    AND_GIVEN("A sphere") {
      auto s = rt::Sphere();
      WHEN("Intersecting") {
        auto xs = s.intersect(ray);
        THEN("") {
          REQUIRE(xs.count() == 0);
        }
      }
    }
  }
}
SCENARIO("A ray originates from inside a sphere") {
  GIVEN("A ray") {
    auto ray = rt::Ray(util::Tuple::point(0,0,0),util::Tuple::vector(0,0,1));
    AND_GIVEN("A sphere") {
      auto s = rt::Sphere();
      WHEN("Intersecting") {
        auto xs = s.intersect(ray);
        THEN("") {
          REQUIRE(xs.count() == 2);
          REQUIRE(xs[0] == -1.0);
          REQUIRE(xs[1] == 1.0);
        }
      }
    }
  }
}
SCENARIO("A sphere is behind the ray") {
  GIVEN("A ray") {
    auto ray = rt::Ray(util::Tuple::point(0,0,5),util::Tuple::vector(0,0,1));
    AND_GIVEN("A sphere") {
      auto s = rt::Sphere();
      WHEN("Intersecting") {
        auto xs = s.intersect(ray);
        THEN("") {
          REQUIRE(xs.count() == 2);
          REQUIRE(xs[0] == -6.0);
          REQUIRE(xs[1] == -4.0);
        }
      }
    }
  }
}

//
// Created by damian on 23.07.2020.
//

#include <catch2/catch.hpp>
#include <Tuple.h>
#include <Matrix.h>
#include <shapes/Group.h>
#include <shapes/Sphere.h>
SCENARIO("Converting a point from world to object space") {
  GIVEN("") {
    auto g1 = std::make_shared<rt::Group>();
    g1->setTransform(util::Matrixd::rotation_y(std::numbers::pi/2));
    auto g2 = std::make_shared<rt::Group>();
    g2->setTransform(util::Matrixd::scaling(2,2,2));
    g1->addChild(g2);
    auto s = std::make_shared<rt::Sphere>();
    s->setTransform(util::Matrixd::translation(5,0,0));
    g2->addChild(s);
    WHEN("") {
      auto p = s->worldToObject(util::Tuple::point(-2,0,-10));
      THEN("") {
        REQUIRE(p == util::Tuple::point(0,0,-1));
      }
    }
  }
}
SCENARIO("Converting a normal from object to world space") {
  GIVEN("") {
    auto g1 = std::make_shared<rt::Group>();
    g1->setTransform(util::Matrixd::rotation_y(std::numbers::pi/2));
    auto g2 = std::make_shared<rt::Group>();
    g2->setTransform(util::Matrixd::scaling(1,2,3));
    g1->addChild(g2);
    auto s = std::make_shared<rt::Sphere>();
    s->setTransform(util::Matrixd::translation(5,0,0));
    g2->addChild(s);
    WHEN("") {
      auto n = s->normalToWorld(util::Tuple::vector(sqrt(3)/3,sqrt(3)/3,sqrt(3)/3));
      THEN("") {
        REQUIRE(n == util::Tuple::vector(0.28571,0.42857,-0.85714));
      }
    }
  }
}

SCENARIO("Finding the normal on a child object") {
  GIVEN("") {
    auto g1 = std::make_shared<rt::Group>();
    g1->setTransform(util::Matrixd::rotation_y(std::numbers::pi/2));
    auto g2 = std::make_shared<rt::Group>();
    g2->setTransform(util::Matrixd::scaling(1,2,3));
    g1->addChild(g2);
    auto s = std::make_shared<rt::Sphere>();
    s->setTransform(util::Matrixd::translation(5,0,0));
    g2->addChild(s);
    WHEN("") {
      auto n = s->normalAt(util::Tuple::point(1.7321,1.1547,-5.5774));
      THEN("") {
        REQUIRE(n == util::Tuple::vector(0.2857,0.42854,-0.85716));
      }
    }
  }
}

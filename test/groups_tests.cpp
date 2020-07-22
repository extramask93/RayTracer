//
// Created by damian on 22.07.2020.
//

#include <catch2/catch.hpp>
#include <shapes/Group.h>
#include <shapes/Sphere.h>
#include <Matrix.h>
SCENARIO("Creating a new group") {
  GIVEN("") {
    auto g = rt::Group();
    THEN("") {
      REQUIRE(g.transform() == util::Matrixd::Identity(4));
      REQUIRE(g.empty() == true);
    }
  }
}
SCENARIO("A shape has a parent atribute") {
  GIVEN("") {
    auto s = rt::Sphere();
    THEN("") {
      REQUIRE(s.parent() == nullptr);
    }
  }
}
SCENARIO("Adding child to a group") {
  GIVEN("") {
    auto g = std::make_shared<rt::Group>();
    auto s = std::make_shared<rt::Sphere>();
    WHEN("") {
      g->addChild(s);
      THEN("") {
        REQUIRE(g->empty() == false);
        REQUIRE(s->parent() == g);
      }
    }
  }
}
SCENARIO("Intersecting a ray with an empty group") {
  GIVEN("") {
    auto g = std::make_shared<rt::Group>();
    auto r = rt::Ray(util::Tuple::point(0,0,0), util::Tuple::vector(0,0,1));
    WHEN("") {
      auto xs = g->localIntersect(r);
      THEN("") {
        REQUIRE(xs.size() == 0);
      }
    }
  }
}
SCENARIO("Intersecting a ray with a nonempty group") {
  GIVEN("") {
    auto g = std::make_shared<rt::Group>();
    auto s1 = std::make_shared<rt::Sphere>();
    auto s2 = std::make_shared<rt::Sphere>();
    auto s3 = std::make_shared<rt::Sphere>();
    g->addChild(s1).addChild(s2).addChild(s3);
    s2->setTransform(util::Matrixd::translation(0,0,-3));
    s3->setTransform(util::Matrixd::translation(5,0,0));
    auto r = rt::Ray(util::Tuple::point(0,0,-5), util::Tuple::vector(0,0,1));
    WHEN("") {
      auto xs = g->localIntersect(r);
      THEN("") {
        REQUIRE(xs.size() == 4);
        REQUIRE(xs[0].object() == s2.get());
        REQUIRE(xs[1].object() == s2.get());
        REQUIRE(xs[2].object() == s1.get());
        REQUIRE(xs[3].object() == s1.get());
      }
    }
  }
}

SCENARIO("Intersecting a transformed group") {
  GIVEN("") {
    auto g = std::make_shared<rt::Group>();
    auto s1 = std::make_shared<rt::Sphere>();
    g->addChild(s1);
    g->setTransform(util::Matrixd::scaling(2,2,2));
    s1->setTransform(util::Matrixd::translation(5,0,0));
    auto r = rt::Ray(util::Tuple::point(10,0,-10), util::Tuple::vector(0,0,1));
    WHEN("") {
      auto xs = g->intersect(r);
      THEN("") {
        REQUIRE(xs.size() == 2);
      }
    }
  }
}

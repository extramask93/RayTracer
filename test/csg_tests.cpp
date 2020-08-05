//
// Created by damian on 29.07.2020.
//
#include <catch2/catch.hpp>
#include <shapes/Sphere.h>
#include <shapes/Cube.h>
#include <shapes/Csg.h>
SCENARIO("CSG is created with an operation and two shapes")
{
  GIVEN("")
  {
    auto s1 = std::make_shared<rt::Sphere>();
    auto s2 = std::make_shared<rt::Cube>();
    WHEN("")
    {
      auto c = rt::Csg::createCsg(rt::CSGOpType::kUnion, s1, s2);
      THEN("")
      {
        REQUIRE(c->operation() == rt::CSGOpType::kUnion);
        REQUIRE(c->left() == s1.get());
        REQUIRE(c->right() == s2.get());
        REQUIRE(s1->parent().get() == c.get());
        REQUIRE(s2->parent().get() == c.get());
      }
    }
  }
}
SCENARIO("Evaluating the rule for a CSG operation")
{
  GIVEN("Truth table with input values and expected outputs")
  {
    const auto truthTable = std::vector<std::tuple<rt::CSGOpType, bool, bool, bool, bool>>{
      { rt::CSGOpType::kUnion, true, true, true, false },
      { rt::CSGOpType::kUnion, true, true, false, true },
      { rt::CSGOpType::kUnion, true, false, true, false },
      { rt::CSGOpType::kUnion, true, false, false, true },
      { rt::CSGOpType::kUnion, false, true, true, false },
      { rt::CSGOpType::kUnion, false, true, false, false },
      { rt::CSGOpType::kUnion, false, false, true, true },
      { rt::CSGOpType::kUnion, false, false, false, true },

      { rt::CSGOpType::kIntersection, true, true, true, true },
      { rt::CSGOpType::kIntersection, true, true, false, false },
      { rt::CSGOpType::kIntersection, true, false, true, true },
      { rt::CSGOpType::kIntersection, true, false, false, false },
      { rt::CSGOpType::kIntersection, false, true, true, true },
      { rt::CSGOpType::kIntersection, false, true, false, true },
      { rt::CSGOpType::kIntersection, false, false, true, false },
      { rt::CSGOpType::kIntersection, false, false, false, false },

      { rt::CSGOpType::kDifference, true, true, true, false },
      { rt::CSGOpType::kDifference, true, true, false, true },
      { rt::CSGOpType::kDifference, true, false, true, false },
      { rt::CSGOpType::kDifference, true, false, false, true },
      { rt::CSGOpType::kDifference, false, true, true, true },
      { rt::CSGOpType::kDifference, false, true, false, true },
      { rt::CSGOpType::kDifference, false, false, true, false },
      { rt::CSGOpType::kDifference, false, false, false, false },
    };
    const auto [op, lhit, inl, inr, re] = GENERATE_COPY(from_range(truthTable));
    WHEN("Checking for an allowed intersection")
    {
      auto result = rt::Csg::intersectionAllowed(op, lhit, inl, inr);
      THEN("One get's correct result")
      {
        REQUIRE(result == re);
      }
    }
  }
}
SCENARIO("Filtering a list of intersections") {
  GIVEN("") {
    auto examples = std::vector<std::tuple<rt::CSGOpType, std::size_t , std::size_t>> {
      {rt::CSGOpType::kUnion, 0, 3},
      {rt::CSGOpType::kIntersection, 1, 2},
      {rt::CSGOpType::kDifference, 0, 1},
    };
    auto [op,x0,x1] = GENERATE_COPY(from_range(examples));
    auto s1 = std::make_shared<rt::Sphere>();
    auto s2 = std::make_shared<rt::Cube>();
    auto c = rt::Csg::createCsg(op,s1,s2);
    auto xs = rt::Intersections{rt::Intersection(1,s1.get()),rt::Intersection(2,s2.get()),rt::Intersection(3,s1.get()),rt::Intersection(4,s2.get())};
    WHEN("") {
      auto result = c->filterIntersections(xs);
      THEN("") {
        REQUIRE(result.size() == 2);
        REQUIRE(result[0] == xs[x0]);
        REQUIRE(result[1] == xs[x1]);
      }
    }
  }
}
SCENARIO("A ray misses a CSG object") {
  auto c = rt::Csg::createCsg(rt::CSGOpType::kUnion, std::make_shared<rt::Sphere>(), std::make_shared<rt::Cube>());
  auto r = rt::Ray(util::Tuple::point(0,2,-5),util::Tuple::vector(0,0,1));
  WHEN("") {
    auto xs = c->localIntersect(r);
    THEN("") {
      REQUIRE(xs.size() == 0);
    }
  }
}

SCENARIO("A ray hits a CSG object") {
  auto s1 =  std::make_shared<rt::Sphere>();
  auto s2 =  std::make_shared<rt::Sphere>();
  s2->setTransform(util::Matrixd::translation(0,0,0.5));
  auto c = rt::Csg::createCsg(rt::CSGOpType::kUnion,s1,s2);
  auto r = rt::Ray(util::Tuple::point(0,0,-5),util::Tuple::vector(0,0,1));
  WHEN("") {
    auto xs = c->localIntersect(r);
    THEN("") {
      REQUIRE(xs.size() == 2);
      REQUIRE(xs[0].t() == 4);
      REQUIRE(xs[0].object() == s1.get());
      REQUIRE(xs[1].t() == 6.5);
      REQUIRE(xs[1].object() == s2.get());
    }
  }
}

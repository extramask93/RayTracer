//
// Created by damian on 21.07.2020.
//

#include <catch2/catch.hpp>
#include <shapes/Cone.h>
#include <intersections/Intersections.h>
#include <vector>
#include <tuple>
#include <Tuple.h>
SCENARIO("Intersecting a cone with a ray")
{
  GIVEN("")
  {
    std::vector<std::tuple<util::Tuple, util::Tuple, double, double>> cases{
      { util::Tuple::point(0, 0, -5), util::Tuple::vector(0, 0, 1), 5, 5 },
      { util::Tuple::point(0, 0, -5), util::Tuple::vector(1, 1, 1), 8.66025, 8.66025 },
      { util::Tuple::point(1, 1, -5), util::Tuple::vector(-0.5, -1, 1), 4.55006, 49.44994 },
    };
    for (const auto &c : cases) {
      auto shape = rt::Cone();
      auto direction = std::get<1>(c);
      auto r = rt::Ray(std::get<0>(c), direction);
      WHEN("")
      {
        auto xs = shape.localIntersect(r);
        THEN("")
        {
          REQUIRE(xs.size() == 2);
          REQUIRE(xs[0].t() == std::get<2>(c));
          REQUIRE(xs[1].t() == std::get<3>(c));
        }
      }
    }
  }
}
SCENARIO("Intersecting a cone with a ray parallel to one of its halves")
{
  GIVEN("")
  {
    auto shape = rt::Cone();
    auto direction = util::Tuple::vector(0, 1, 1).normalization();
    auto r = rt::Ray(util::Tuple::point(0, 0, -1), direction);
    WHEN("")
    {
      auto xs = shape.localIntersect(r);
      THEN("")
      {
        REQUIRE(xs.size() == 1);
        REQUIRE(xs[0].t() == Approx(0.35355));
      }
    }
  }
}
SCENARIO("Intersecting a cone's end caps")
{
  GIVEN("")
  {
    auto shape = rt::Cone();
    shape.minimum() = -0.5;
    shape.maximum() = 0.5;
    shape.closed() = true;
    std::vector<std::tuple<util::Tuple, util::Tuple, std::size_t>> cases{
      { util::Tuple::point(0, 0, -5), util::Tuple::vector(0, 1, 0), 0 },
      { util::Tuple::point(0, 0, -0.25), util::Tuple::vector(0, 1, 1), 2 },
      { util::Tuple::point(0, 0, -0.25), util::Tuple::vector(0, 1, 0), 4 },
    };
    for (const auto &c : cases) {
      auto direction = std::get<1>(c).normalization();
      auto r = rt::Ray(std::get<0>(c), direction);
      WHEN("")
      {
        auto xs = shape.localIntersect(r);
        THEN("")
        {
          REQUIRE(xs.size() == std::get<2>(c));
        }
      }
    }
  }
}
SCENARIO("Computing the normal vector on a cone") {
  GIVEN("") {
    auto shape = rt::Cone();
    std::vector<std::tuple<util::Tuple, util::Tuple>> cases {
      {util::Tuple::point(0,0,0), util::Tuple::vector(0,0,0)},
      {util::Tuple::point(1,1,1), util::Tuple::vector(1,-sqrt(2),1)},
      {util::Tuple::point(-1,-1,0), util::Tuple::vector(-1,1,0)},
    };
    for(const auto &c : cases) {
      WHEN("")
      {
        auto n = shape.localNormalAt(std::get<0>(c));
        THEN("")
        {
          REQUIRE(n == std::get<1>(c));
        }
      }
    }
  }
}
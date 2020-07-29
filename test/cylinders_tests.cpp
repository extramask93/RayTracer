//
// Created by damian on 21.07.2020.
//
#include <catch2/catch.hpp>
#include <shapes/Cylinder.h>
#include <intersections/Intersections.h>
#include <Tuple.h>
#include <tuple>
SCENARIO("A ray misses a cylinder")
{
  GIVEN("")
  {
    std::vector<std::tuple<util::Tuple, util::Tuple>> cases{
      { util::Tuple::point(1, 0, 0), util::Tuple::vector(0, 1, 0) },
      { util::Tuple::point(0, 0, 0), util::Tuple::vector(0, 1, 0) },
      { util::Tuple::point(0, 0, -5), util::Tuple::vector(1, 1, 1) },
    };
    auto cyl = rt::Cylinder();
    for (const auto &c : cases) {
      auto direction = std::get<1>(c);
      auto r = rt::Ray(std::get<0>(c), direction);
      WHEN("")
      {
        auto xs = cyl.localIntersect(r);
        THEN("")
        {
          REQUIRE(xs.size() == 0);
        }
      }
    }
  }
}
SCENARIO("A ray strikes a cylinder")
{
  GIVEN("")
  {
    std::vector<std::tuple<util::Tuple, util::Tuple, double, double>> cases{
      { util::Tuple::point(1, 0, -5), util::Tuple::vector(0, 0, 1), 5, 5 },
      { util::Tuple::point(0, 0, -5), util::Tuple::vector(0, 0, 1), 4, 6 },
      { util::Tuple::point(0.5, 0, -5), util::Tuple::vector(0.1, 1, 1), 6.80798, 7.08872 },
    };
    auto cyl = rt::Cylinder();
    for (const auto &c : cases) {
      auto direction = std::get<1>(c);
      auto r = rt::Ray(std::get<0>(c), direction);
      WHEN("")
      {
        auto xs = cyl.localIntersect(r);
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

SCENARIO("Normal vector on a cylinder")
{
  GIVEN("")
  {
    std::vector<std::tuple<util::Tuple, util::Tuple>> cases{
      { util::Tuple::point(1, 0, 0), util::Tuple::vector(1, 0, 0) },
      { util::Tuple::point(0, 5, -1), util::Tuple::vector(0, 0, -1) },
      { util::Tuple::point(0, -2, 1), util::Tuple::vector(0, 0, 1) },
      { util::Tuple::point(-1, 1, 0), util::Tuple::vector(-1, 0, 0) },
    };
    auto cyl = rt::Cylinder();
    for (const auto &c : cases) {
      WHEN("")
      {
        auto n = cyl.localNormalAt(std::get<0>(c), rt::Intersection(0, nullptr));
        THEN("")
        {
          REQUIRE(n == std::get<1>(c));
        }
      }
    }
  }
}
SCENARIO("Minimum and maximum bounds")
{
  GIVEN("")
  {
    auto cul = rt::Cylinder();
    THEN("")
    {
      REQUIRE(cul.minimum() == -std::numeric_limits<double>::infinity());
      REQUIRE(cul.maximum() == std::numeric_limits<double>::infinity());
    }
  }
}
SCENARIO("Intersecting a constrained cylinder")
{
  GIVEN("")
  {
    auto cyl = rt::Cylinder();
    cyl.maximum() = 2;
    cyl.minimum() = 1;
    std::vector<std::tuple<util::Tuple, util::Tuple, std::size_t>> cases{
      { util::Tuple::point(0, 1.5, 0), util::Tuple::vector(0.1, 1, 0), 0 },
      { util::Tuple::point(0, 3, -5), util::Tuple::vector(0, 0, 1), 0 },
      { util::Tuple::point(0, 0, -5), util::Tuple::vector(0, 0, 1), 0 },
      { util::Tuple::point(0, 2, -5), util::Tuple::vector(0, 0, 1), 0 },
      { util::Tuple::point(0, 1, -5), util::Tuple::vector(0, 0, 1), 0 },
      { util::Tuple::point(0, 1.5, -2), util::Tuple::vector(0, 0, 1), 2 },
    };
    for (const auto &c : cases) {
      auto direction = std::get<1>(c).normalization();
      auto r = rt::Ray(std::get<0>(c), direction);
      WHEN("")
      {
        auto xs = cyl.localIntersect(r);
        THEN("")
        {
          REQUIRE(xs.size() == std::get<2>(c));
        }
      }
    }
  }
}
SCENARIO("The default closed value for a cylinder") {
  GIVEN("") {
    auto cyl = rt::Cylinder();
    THEN("") {
      REQUIRE(cyl.closed() == false);
    }
  }
}
SCENARIO("Intersecting the caps of a closed cylinder")
{
  GIVEN("")
  {
    auto cyl = rt::Cylinder();
    cyl.maximum() = 2;
    cyl.minimum() = 1;
    cyl.closed() = true;
    std::vector<std::tuple<util::Tuple, util::Tuple, std::size_t>> cases{
      { util::Tuple::point(0, 3, 0), util::Tuple::vector(0, -1, 0), 2 },
      { util::Tuple::point(0, 3, -2), util::Tuple::vector(0, -1, 2), 2 },
      { util::Tuple::point(0, 4, -2), util::Tuple::vector(0, -1, 1), 2 },
      { util::Tuple::point(0, 0, -2), util::Tuple::vector(0, 1, 2), 2 },
      { util::Tuple::point(0, -1, -2), util::Tuple::vector(0, 1, 1), 2 },
    };
    for (const auto &c : cases) {
      auto direction = std::get<1>(c).normalization();
      auto r = rt::Ray(std::get<0>(c), direction);
      WHEN("")
      {
        auto xs = cyl.localIntersect(r);
        THEN("")
        {
          REQUIRE(xs.size() == std::get<2>(c));
        }
      }
    }
  }
}

SCENARIO("Normal vector on a cylinder's end caps")
{
  GIVEN("")
  {
    std::vector<std::tuple<util::Tuple, util::Tuple>> cases{
      { util::Tuple::point(0, 1, 0), util::Tuple::vector(0, -1, 0) },
      { util::Tuple::point(0.5,1,0), util::Tuple::vector(0, -1, 0) },
      { util::Tuple::point(0, 1, 0.5), util::Tuple::vector(0, -1, 0) },
      { util::Tuple::point(0, 2, 0), util::Tuple::vector(0, 1, 0) },
      { util::Tuple::point(0.5, 2, 0), util::Tuple::vector(0, 1, 0) },
      { util::Tuple::point(0, 2, 0.5), util::Tuple::vector(0, 1, 0) },
    };
    auto cyl = rt::Cylinder();
    cyl.minimum() = 1;
    cyl.maximum() =2;
    cyl.closed() =true;
    for (const auto &c : cases) {
      WHEN("")
      {
        auto n = cyl.localNormalAt(std::get<0>(c), rt::Intersection(0, nullptr));
        THEN("")
        {
          REQUIRE(n == std::get<1>(c));
        }
      }
    }
  }
}

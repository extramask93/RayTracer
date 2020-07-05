//
// Created by damian on 05.07.2020.
//

#include <catch2/catch.hpp>
#include <Matrix.h>
#include <Tuple.h>
#include <cmath>

SCENARIO("Multiplying by translation matrix")
{
  GIVEN("Transform matrix")
  {
    auto transform = util::Matrix<double>::translation(5, -3, 2);
    auto point = util::Tuple::point(-3, 4, 5);
    THEN("point*transform == point(2,1,7)")
    {
      REQUIRE(transform * point == util::Tuple::point(2, 1, 7));
    }
  }
}
SCENARIO("Multiplying by inverse of translation matrix")
{
  GIVEN("Transform matrix")
  {
    auto transform = util::Matrix<double>::translation(5, -3, 2);
    auto inverse = transform.inverse();
    auto point = util::Tuple::point(-3, 4, 5);
    THEN("point*transform == point(2,1,7)")
    {
      REQUIRE(inverse * point == util::Tuple::point(-8, 7, 3));
    }
  }
}
SCENARIO("Translation does not affect vectors")
{
  GIVEN("Transform matrix")
  {
    auto transform = util::Matrix<double>::translation(5, -3, 2);
    auto vector = util::Tuple::vector(-3, 4, 5);
    THEN("point*transform == point(2,1,7)")
    {
      REQUIRE(transform * vector == vector);
    }
  }
}
SCENARIO("Scaling by a matrix")
{
  GIVEN("Transform matrix")
  {
    auto transform = util::Matrix<double>::scaling(2, 3, 4);
    auto point = util::Tuple::point(-4, 6, 8);
    THEN("point*transform == point(-8,18,32)")
    {
      REQUIRE(transform * point == util::Tuple::point(-8, 18, 32));
    }
  }
}
SCENARIO("Scaling by a inverse matrix")
{
  GIVEN("Transform matrix")
  {
    auto transform = util::Matrix<double>::scaling(2, 3, 4);
    auto inverse = transform.inverse();
    auto point = util::Tuple::point(-4, 6, 8);
    THEN("point*inverse == point(-2,2,2)")
    {
      REQUIRE(inverse * point == util::Tuple::point(-2, 2, 2));
    }
  }
}
SCENARIO("Reflection is scaling by a negative value")
{
  GIVEN("Transform matrix")
  {
    auto transform = util::Matrix<double>::scaling(-1, 1, 1);
    auto point = util::Tuple::point(-4, 6, 8);
    THEN("point*transform == point(4,6,8)")
    {
      REQUIRE(transform * point == util::Tuple::point(4, 6, 8));
    }
  }
}
SCENARIO("Rotating a point around x axis")
{
  GIVEN("Transform matrix")
  {
    auto point = util::Tuple::point(0, 1, 0);
    auto half_quarter = util::Matrix<double>::rotation_x(M_PI / 4);
    auto full_quarter = util::Matrix<double>::rotation_x(M_PI / 2);
    THEN(" ")
    {
      REQUIRE(full_quarter * point == util::Tuple::point(0, 0, 1));
      REQUIRE(half_quarter * point == util::Tuple::point(0, sqrt(2) / 2, sqrt(2) / 2));
    }
  }
}
SCENARIO("Rotating by inverse rotates point around x axis in opposite direction")
{
  GIVEN("Transform matrix")
  {
    auto point = util::Tuple::point(0, 1, 0);
    auto half_quarter = util::Matrix<double>::rotation_x(M_PI / 4);
    auto full_quarter = util::Matrix<double>::rotation_x(M_PI / 2);
    THEN(" ")
    {
      REQUIRE(full_quarter.inverse() * point == util::Tuple::point(0, 0, -1));
      REQUIRE(half_quarter.inverse() * point == util::Tuple::point(0, sqrt(2) / 2, -sqrt(2) / 2));
    }
  }
}
SCENARIO("Rotating a point around y axis")
{
  GIVEN("Transform matrix")
  {
    auto point = util::Tuple::point(0, 0, 1);
    auto half_quarter = util::Matrix<double>::rotation_y(M_PI / 4);
    auto full_quarter = util::Matrix<double>::rotation_y(M_PI / 2);
    THEN(" ")
    {
      REQUIRE(full_quarter * point == util::Tuple::point(1, 0, 0));
      REQUIRE(half_quarter * point == util::Tuple::point(sqrt(2) / 2, 0, sqrt(2) / 2));
    }
  }
}
SCENARIO("Rotating a point around z axis")
{
  GIVEN("Transform matrix")
  {
    auto point = util::Tuple::point(0, 1, 0);
    auto half_quarter = util::Matrix<double>::rotation_z(M_PI / 4);
    auto full_quarter = util::Matrix<double>::rotation_z(M_PI / 2);
    THEN(" ")
    {
      REQUIRE(full_quarter * point == util::Tuple::point(-1, 0, 0));
      REQUIRE(half_quarter * point == util::Tuple::point(-sqrt(2) / 2, sqrt(2) / 2, 0));
    }
  }
}
SCENARIO("A Shearing transformation moves x in proportion to y")
{
  GIVEN("Transform shearing(1,0,0,0,0,0)")
  {
    auto transform = util::Matrix<double>::shearing(1,0,0,0,0,0);
    AND_GIVEN("point(2,3,4)")
    {
      auto point = util::Tuple::point(2,3,4);
      THEN("transform * p  = point(5,3,4)")
      {
      REQUIRE(transform*point == util::Tuple::point(5,3,4));
      }
    }
  }
}
SCENARIO("A Shearing transformation moves x in proportion to z")
{
  GIVEN("Transform shearing(0,1,0,0,0,0)")
  {
    auto transform = util::Matrix<double>::shearing(0,1,0,0,0,0);
    AND_GIVEN("point(2,3,4)")
    {
      auto point = util::Tuple::point(2,3,4);
      THEN("transform * p  = point(6,3,4)")
      {
        REQUIRE(transform*point == util::Tuple::point(6,3,4));
      }
    }
  }
}
SCENARIO("A Shearing transformation moves y in proportion to x")
{
  GIVEN("Transform shearing(0,1,0,0,0,0)")
  {
    auto transform = util::Matrix<double>::shearing(0,0,1,0,0,0);
    AND_GIVEN("point(2,3,4)")
    {
      auto point = util::Tuple::point(2,3,4);
      THEN("transform * p  = point(2,5,4)")
      {
        REQUIRE(transform*point == util::Tuple::point(2,5,4));
      }
    }
  }
}
SCENARIO("A Shearing transformation moves y in proportion to z")
{
  GIVEN("Transform shearing(0,0,0,1,0,0)")
  {
    auto transform = util::Matrix<double>::shearing(0,0,0,1,0,0);
    AND_GIVEN("point(2,3,4)")
    {
      auto point = util::Tuple::point(2,3,4);
      THEN("transform * p  = point(2,7,4)")
      {
        REQUIRE(transform*point == util::Tuple::point(2,7,4));
      }
    }
  }
}
SCENARIO("A Shearing transformation moves z in proportion to x")
{
  GIVEN("Transform shearing(0,0,0,0,1,0)")
  {
    auto transform = util::Matrix<double>::shearing(0,0,0,0,1,0);
    AND_GIVEN("point(2,3,4)")
    {
      auto point = util::Tuple::point(2,3,4);
      THEN("transform * p  = point(2,3,6)")
      {
        REQUIRE(transform*point == util::Tuple::point(2,3,6));
      }
    }
  }
}
SCENARIO("A Shearing transformation moves z in proportion to y")
{
  GIVEN("Transform shearing(0,0,0,0,0,1)")
  {
    auto transform = util::Matrix<double>::shearing(0,0,0,0,0,1);
    AND_GIVEN("point(2,3,4)")
    {
      auto point = util::Tuple::point(2,3,4);
      THEN("transform * p  = point(2,3,7)")
      {
        REQUIRE(transform*point == util::Tuple::point(2,3,7));
      }
    }
  }
}
SCENARIO("Individual transformations are applied in sequence")
{
  GIVEN("Transform shearing(0,0,0,0,0,1)")
  {
    auto point = util::Tuple::point(1,0,1);
    AND_GIVEN("rotation matrix")
    {
      auto A = util::Matrix<double>::rotation_x(M_PI/2);
      AND_GIVEN("scaling matrix") {
        auto B =util::Matrix<double>::scaling(5,5,5);
        AND_GIVEN("Translation matrix") {
          auto C = util::Matrix<double>::translation(10,5,7);
          WHEN("") {
            auto p2 = A* point;
            THEN("") {
              REQUIRE(p2 == util::Tuple::point(1,-1,0));
            }
            AND_WHEN("") {
              auto p3 = B * p2;
              THEN("") {
                REQUIRE(p3 == util::Tuple::point(5,-5,0));
              }
              AND_WHEN("") {
                auto p4 = C*p3;
                THEN("") {
                  REQUIRE(p4 == util::Tuple::point(15,0,7));
                }
              }
            }
          }
        }
      }
    }
  }
}
SCENARIO("Chained transformations must be applied in reverse order") {
GIVEN("") {
  auto p = util::Tuple::point(1,0,1);
  AND_GIVEN("") {
    auto A= util::Matrix<double>::rotation_x(M_PI/2);
    AND_GIVEN("") {
        auto B= util::Matrix<double>::scaling(5,5,5);
        AND_GIVEN("") {
          auto C= util::Matrix<double>::translation(10,5,7);
          WHEN("") {
            auto T = C*B*A;
            THEN("") {
              REQUIRE(T*p == util::Tuple::point(15,0,7));
            }
          }
        }
    }
  }
}
}
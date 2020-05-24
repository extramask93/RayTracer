#include <catch2/catch.hpp>
#include <Tuple.h>
unsigned int Factorial(unsigned int number)
{
  return number <= 1 ? number : Factorial(number - 1) * number;
}

TEST_CASE("Factorials are computed", "[factorial]")
{
  REQUIRE(Factorial(1) == 1);
  REQUIRE(Factorial(2) == 2);
  REQUIRE(Factorial(3) == 6);
  REQUIRE(Factorial(10) == 3628800);
}
SCENARIO("A tuple with w = 1.0 is a point")
{
  GIVEN("Vector a with w set to 1.0")
  {
    util::Tuple a(4.3, -4.2, 3.1, 1.0);
    THEN("a.x is set properly ")
    {
      REQUIRE(a.x == 4.3);
    }
    AND_THEN("a.y is set properly")
    {
      REQUIRE(a.y == -4.2);
    }
    AND_THEN("a.z is set properly")
    {
      REQUIRE(a.z == 3.1);
    }
    AND_THEN("a.w is equal to  1.0")
    {
      REQUIRE(a.w == 1.0);
    }
    AND_THEN("a is a point")
    {
      REQUIRE(a.isPoint() == true);
    }
    AND_THEN("a is not a vector")
    {
      REQUIRE(a.isVector() == false);
    }
  }
}
SCENARIO("A tuple with w = 0.0 is a vector")
{
  GIVEN("Vector a with w set to 1.0")
  {
    util::Tuple a(4.3, -4.2, 3.1, 0.0);
    THEN("a.x is set properly ")
    {
      REQUIRE(a.x == 4.3);
    }
    AND_THEN("a.y is set properly")
    {
      REQUIRE(a.y == -4.2);
    }
    AND_THEN("a.z is set properly")
    {
      REQUIRE(a.z == 3.1);
    }
    AND_THEN("a.w is equal to  1.0")
    {
      REQUIRE(a.w == 0.0);
    }
    AND_THEN("a is a point")
    {
      REQUIRE(a.isPoint() == false);
    }
    AND_THEN("a is not a vector")
    {
      REQUIRE(a.isVector() == true);
    }
  }
}
SCENARIO("point() creates tuples with w==1")
{
  GIVEN("p = point(4,-4,3)")
  {
    util::Tuple p = util::Tuple::point(4, -4, 3);
    THEN("p == tuple(4,-4,3,1.0)")
    {
      REQUIRE(p == util::Tuple(4, -4, 3, 1));
    }
  }
}
SCENARIO("vector() creates tuples with w==0")
{
  GIVEN("p = vector(4,-4,3)")
  {
    util::Tuple p = util::Tuple::vector(4, -4, 3);
    THEN("p == tuple(4,-4,3,0.0)")
    {
      REQUIRE(p == util::Tuple(4, -4, 3, 0.0));
    }
  }
}
SCENARIO("Adding two tuples")
{
  GIVEN("p1 = tuple(3,-2,5,1)")
  {
    auto p1 = util::Tuple::point(3, -2, 5);
    AND_GIVEN("p2 = tuple(-2,3,1,0")
    {
      auto p2 = util::Tuple::vector(-2, 3, 1);
      THEN("p == tuple(1,1,6,1.0)")
      {
        REQUIRE(p1 + p2 == util::Tuple(1, 1, 6, 1.0));
      }
    }
  }
}
SCENARIO("Subtracting two points")
{
  GIVEN("p1 = tuple(3,-2,5,1)")
  {
    auto p1 = util::Tuple::point(3, 2, 1);
    AND_GIVEN("p2 = tuple(-2,3,1,0")
    {
      auto p2 = util::Tuple::point(5, 6, 7);
      THEN("p == tuple(1,1,6,1.0)")
      {
        REQUIRE(p1 - p2 == util::Tuple::vector(-2, -4, -6));
      }
    }
  }
}
SCENARIO("Subtracting vector from a point")
{
  GIVEN("p1 = tuple(3,-2,5,1)")
  {
    auto p1 = util::Tuple::point(3, 2, 1);
    AND_GIVEN("p2 = tuple(-2,3,1,0")
    {
      auto p2 = util::Tuple::vector(5, 6, 7);
      THEN("p == tuple(1,1,6,1.0)")
      {
        REQUIRE(p1 - p2 == util::Tuple::point(-2, -4, -6));
      }
    }
  }
}
SCENARIO("Subtracting two vectors")
{
  GIVEN("p1 = tuple(3,-2,5,1)")
  {
    auto p1 = util::Tuple::vector(3, 2, 1);
    AND_GIVEN("p2 = tuple(-2,3,1,0")
    {
      auto p2 = util::Tuple::vector(5, 6, 7);
      THEN("p == tuple(1,1,6,1.0)")
      {
        REQUIRE(p1 - p2 == util::Tuple::vector(-2, -4, -6));
      }
    }
  }
}

#include <catch2/catch.hpp>
#include <Tuple.h>

SCENARIO("A tuple with w = 1.0 is a point")
{
  GIVEN("Vector a with w set to 1.0")
  {
    util::Tuple a(4.3, -4.2, 3.1, 1.0);
    THEN("a.x() is set proper.y() ")
    {
      REQUIRE(a.x() == 4.3);
    }
    AND_THEN("a.y() is set proper.y()")
    {
      REQUIRE(a.y() == -4.2);
    }
    AND_THEN("a.z is set proper.y()")
    {
      REQUIRE(a.z() == 3.1);
    }
    AND_THEN("a.w is equal to  1.0")
    {
      REQUIRE(a.w() == 1.0);
    }
    AND_THEN("a is a point")
    {
      REQUIRE(a.isPoint());
    }
    AND_THEN("a is not a vector")
    {
      REQUIRE(!a.isVector());
    }
  }
}
SCENARIO("A tuple with w = 0.0 is a vector")
{
  GIVEN("Vector a with w set to 1.0")
  {
    util::Tuple a(4.3, -4.2, 3.1, 0.0);
    THEN("a.x() is set proper.y() ")
    {
      REQUIRE(a.x() == 4.3);
    }
    AND_THEN("a.y() is set proper.y()")
    {
      REQUIRE(a.y() == -4.2);
    }
    AND_THEN("a.z is set proper.y()")
    {
      REQUIRE(a.z() == 3.1);
    }
    AND_THEN("a.w is equal to  1.0")
    {
      REQUIRE(a.w() == 0.0);
    }
    AND_THEN("a is a point")
    {
      REQUIRE(!a.isPoint());
    }
    AND_THEN("a is not a vector")
    {
      REQUIRE(a.isVector());
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
SCENARIO("Subtracting  a vector from the zero vector")
{
  GIVEN("zero = vector(0,0,0)")
  {
    auto zero = util::Tuple::vector(0, 0, 0);
    AND_GIVEN("v = vector(1,-2,3)")
    {
      auto v = util::Tuple::vector(1, -2, 3);
      THEN("zero - v  == vector(-1,2,-3)")
      {
        REQUIRE((zero - v) == util::Tuple::vector(-1, 2, -3));
      }
    }
  }
}
SCENARIO("Negating a tuple")
{
  GIVEN("a <- tuple (1,-2,3,-4)")
  {
    auto a = util::Tuple(1, -2, 3, -4);
    THEN("-a = tuple(-1,2,-3,4)")
    {
      REQUIRE(-a == util::Tuple(-1, 2, -3, 4));
    }
  }
}
SCENARIO("Multip.y()ing .y() scalar")
{
  GIVEN("a = tuple(1,-2,3,-4)")
  {
    auto a = util::Tuple(1, -2, 3, -4);
    THEN("a*3.5 = tuple(3.5,-7,10.5,-14)")
    {
      REQUIRE(a * 3.5 == util::Tuple(3.5, -7, 10.5, -14));
    }
  }
}

SCENARIO("Dividing .y() scalar")
{
  GIVEN("a = tuple(1,-2,3,-4)")
  {
    auto a = util::Tuple(1, -2, 3, -4);
    THEN("a/2 = tuple(0.5,-1,1.5,-2)")
    {
      REQUIRE(a / 2 == util::Tuple(0.5, -1, 1.5, -2));
    }
  }
}
SCENARIO("Computing the magnitude of vector")
{
  GIVEN("v = vector(1,0,0)")
  {
    auto v = util::Tuple::vector(1, 0, 0);
    THEN("magnitude(v) = 1")
    {
      REQUIRE(v.magnitude() == 1);
    }
  }
  GIVEN("v = vector(0,1,0)")
  {
    auto v = util::Tuple::vector(0, 1, 0);
    THEN("magnitude(v) = 1")
    {
      REQUIRE(v.magnitude() == 1);
    }
  }
  GIVEN("v = vector(0,0,1)")
  {
    auto v = util::Tuple::vector(0, 0, 1);
    THEN("magnitude(v) = 1")
    {
      REQUIRE(v.magnitude() == 1);
    }
  }
  GIVEN("v = vector(1,2,3)")
  {
    auto v = util::Tuple::vector(1, 2, 3);
    THEN("magnitude(v) = sqrt(14)")
    {
      REQUIRE(v.magnitude() == std::sqrt(14));
    }
  }
  GIVEN("v = vector(-1,-2,-3)")
  {
    auto v = util::Tuple::vector(-1, -2, -3);
    THEN("magnitude(v) = sqrt(14)")
    {
      REQUIRE(v.magnitude() == std::sqrt(14));
    }
  }
}

SCENARIO("Narmalizing vectors")
{
  GIVEN("v = vector(4,0,0)")
  {
    auto v = util::Tuple::vector(4, 0, 0);
    THEN("normalize(v) = vector(1,0,0)")
    {
      REQUIRE(v.normalize() == util::Tuple::vector(1, 0, 0));
    }
  }
  GIVEN("v = vector(1,2,3)")
  {
    auto v = util::Tuple::vector(1, 2, 3);
    THEN("normalize(v) = vector(1/sqrt(14),2/sqrt(14),3/sqrt(14))")
    {
      REQUIRE(v.normalize() == util::Tuple::vector(0.26726, 0.53452, 0.80178));
    }
  }
}

SCENARIO("Dot product of two tuples")
{
  GIVEN("a = vector(4,0,0)")
  {
    auto a = util::Tuple::vector(1, 2, 3);
    AND_GIVEN("b = vector(2,3,4)")
    {
      auto b = util::Tuple::vector(2, 3, 4);
      THEN("dot(a,b) = 20")
      {
        REQUIRE(a.dot(b) == 20);
      }
    }
  }
}

SCENARIO("Cross product of two tuples")
{
  GIVEN("a = vector(1,2,3)")
  {
    auto a = util::Tuple::vector(1, 2, 3);
    AND_GIVEN("b = vector(2,3,4)")
    {
      auto b = util::Tuple::vector(2, 3, 4);
      THEN("cross(a,b) = vector(-1,2,-1)")
      {
        REQUIRE(a.cross(b) == util::Tuple::vector(-1,2,-1));
        AND_THEN("cross(b,a) = vector(1,-2,1)") {
          REQUIRE(b.cross(a) == util::Tuple::vector(1,-2,1));
        }
      }
    }
  }
}

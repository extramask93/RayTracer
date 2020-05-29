//
// Created by damian on 29.05.2020.
//

#include <catch2/catch.hpp>
#include <Color.h>

SCENARIO("Adding two colors")
{
  GIVEN("color c1 and c2")
  {
    util::Color c1 = util::Color(0.5,0.7,0.1);
    util::Color c2 = util::Color(0.7,0.2,0.9);
    THEN("c1+ c2 = (1.2,0.9,1.0) ")
    {
      REQUIRE(c1+c2 == util::Color(1.2,0.9,1.0));
    }
  }
}
SCENARIO("Subtracting two colors")
{
  GIVEN("color c1 and c2")
  {
    util::Color c1 = util::Color(0.9,0.7,1.0);
    util::Color c2 = util::Color(0.7,0.2,0.9);
    THEN("c1- c2 = (0.2,0.5,0.1) ")
    {
      REQUIRE(c1-c2 == util::Color(0.2,0.5,0.1));
    }
  }
}

SCENARIO("Multiplying two colors")
{
  GIVEN("color c1 and c2")
  {
    util::Color c1 = util::Color(0.9,0.7,1.0);
    util::Color c2 = util::Color(0.1,1.0,0);
    THEN("c1* c2 = (0.09,0.7,0) ")
    {
      REQUIRE(c1*c2 == util::Color(0.09,0.7,0));
    }
  }
}
SCENARIO("color by scalar")
{
  GIVEN("color c1 and scalar")
  {
    util::Color c1 = util::Color(0.9,0.7,1.0);
    double d = 0.5;
    THEN("c1*d = (0.45,0.35,0.5) ")
    {
      REQUIRE(c1*d == util::Color(0.45,0.35,0.5));
    }
  }
}

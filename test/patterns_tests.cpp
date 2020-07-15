//
// Created by damian on 13.07.2020.
//

#include <catch2/catch.hpp>
#include <Color.h>
#include <patterns/StripePattern.h>
#include <patterns/LinearGradientPattern.h>
#include <misc/Computations.h>
#include <shapes/Sphere.h>
#include <patterns/RingPattern.h>
#include <patterns/CheckersPattern.h>
SCENARIO("Stripped pattern")
{
  GIVEN("")
  {
    auto black = util::Color(0, 0, 0);
    auto white = util::Color(1, 1, 1);
    WHEN("Creating a stripe pattern")
    {
      auto pattern = rt::StripePattern(white, black);
      THEN("")
      {
        REQUIRE(pattern.a() == white);
        REQUIRE(pattern.b() == black);
      }
    }
    WHEN("A stripe pattern is constant in y")
    {
      auto pattern = rt::StripePattern(white, black);
      THEN("")
      {
        REQUIRE(pattern.patternAt( util::Tuple::point(0, 0, 0)) == white);
        REQUIRE(pattern.patternAt( util::Tuple::point(0, 1, 0)) == white);
        REQUIRE(pattern.patternAt(  util::Tuple::point(0, 2, 0)) == white);
      }
    }
    WHEN("A stripe pattern is constant in z")
    {
      auto pattern = rt::StripePattern(white, black);
      THEN("")
      {
        REQUIRE(pattern.patternAt(  util::Tuple::point(0, 0, 0)) == white);
        REQUIRE(pattern.patternAt(  util::Tuple::point(0, 0, 1)) == white);
        REQUIRE(pattern.patternAt(  util::Tuple::point(0, 0, 2)) == white);
      }
    }
    WHEN("A stripe pattern alternates in x")
    {
      auto pattern = rt::StripePattern(white, black);
      THEN("")
      {
        REQUIRE(pattern.patternAt(  util::Tuple::point(0, 0, 0)) == white);
        REQUIRE(pattern.patternAt(  util::Tuple::point(0.9, 0, 0)) == white);
        REQUIRE(pattern.patternAt(  util::Tuple::point(1, 0, 0)) == black);
        REQUIRE(pattern.patternAt(  util::Tuple::point(-0.1, 0, 0)) == black);
        REQUIRE(pattern.patternAt(  util::Tuple::point(-1, 0, 0)) == black);
        REQUIRE(pattern.patternAt(  util::Tuple::point(-1.1, 0, 0)) == white);
      }
    }
    WHEN("Stripes with an object transformation")
    {
      auto sphere = rt::Sphere();
      sphere.setTransform(util::Matrixd::scaling(2, 2, 2));
      auto pattern = rt::StripePattern(white,black);
      auto c = rt::patternAtObject(pattern, sphere, util::Tuple::point(1.5, 0, 0));
      THEN("")
      {
        REQUIRE(c == white);
      }
    }
    WHEN("Stripes with pattern transformation")
    {
      auto sphere = rt::Sphere();
      auto pattern = rt::StripePattern(white,black);
      pattern.transform() = util::Matrixd::scaling(2,2,2);
      auto c = rt::patternAtObject(pattern, sphere, util::Tuple::point(1.5, 0, 0));
      THEN("")
      {
        REQUIRE(c == white);
      }
    }

    WHEN("Stripes with both and object and a pattern transformation")
    {
      auto sphere = rt::Sphere();
      sphere.setTransform(util::Matrixd::scaling(2, 2, 2));
      auto pattern = rt::StripePattern(white,black);
      pattern.transform()=util::Matrixd::translation(0.5,0,0);
      auto c = rt::patternAtObject(pattern, sphere, util::Tuple::point(2.5, 0, 0));
      THEN("")
      {
        REQUIRE(c == white);
      }
    }

    WHEN("A gradient linearly interpolates between colors")
    {
      auto pattern = rt::LinearGradientPattern(white,black);
      THEN("")
      {
        REQUIRE(pattern.patternAt(util::Tuple::point(0,0,0)) == white);
        REQUIRE(pattern.patternAt(util::Tuple::point(0.25,0,0)) == util::Color(0.75,0.75,0.75));
        REQUIRE(pattern.patternAt(util::Tuple::point(0.5,0,0)) == util::Color(0.5,0.5,0.5));
        REQUIRE(pattern.patternAt(util::Tuple::point(0.75,0,0)) == util::Color(0.25,0.25,0.25));

      }
    }

    WHEN("A ring should extend in both x and z")
    {
      auto pattern = rt::RingPattern(white,black);
      THEN("")
      {
        REQUIRE(pattern.patternAt(util::Tuple::point(0,0,0)) == white);
        REQUIRE(pattern.patternAt(util::Tuple::point(1,0,0)) == black);
        REQUIRE(pattern.patternAt(util::Tuple::point(0,0,1)) == black);
        REQUIRE(pattern.patternAt(util::Tuple::point(0.708,0,0.708)) == black);

      }
    }
    WHEN("Checkers should repeat in x")
    {
      auto pattern = rt::CheckersPattern(white,black);
      THEN("")
      {
        REQUIRE(pattern.patternAt(util::Tuple::point(0,0,0)) == white);
        REQUIRE(pattern.patternAt(util::Tuple::point(0.99,0,0)) == white);
        REQUIRE(pattern.patternAt(util::Tuple::point(1.01,0,0)) == black);
      }
    }

    WHEN("Checkers should repeat in y")
    {
      auto pattern = rt::CheckersPattern(white,black);
      THEN("")
      {
        REQUIRE(pattern.patternAt(util::Tuple::point(0,0,0)) == white);
        REQUIRE(pattern.patternAt(util::Tuple::point(0,0.99,0)) == white);
        REQUIRE(pattern.patternAt(util::Tuple::point(0,1.01,0)) == black);
      }
    }
  }
}
SCENARIO("The default pattern transformation") {
  GIVEN("Pattern") {
    auto pattern = rt::StripePattern(util::Color(0,0,0), util::Color(1,1,1));
    THEN("") {
      REQUIRE(pattern.transform() == util::Matrixd::Identity(4));
    }
  }
}

SCENARIO("Assigning a transformation") {
  GIVEN("Pattern") {
    auto pattern = rt::StripePattern(util::Color(0,0,0), util::Color(1,1,1));
    pattern.transform() = util::Matrixd::translation(1,2,3);
    THEN("") {
      REQUIRE(pattern.transform() ==util::Matrixd::translation(1,2,3));
    }
  }
}

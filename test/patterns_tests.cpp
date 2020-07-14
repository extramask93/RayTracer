//
// Created by damian on 13.07.2020.
//

#include <catch2/catch.hpp>
#include <Color.h>
#include <patterns/StripePattern.h>
#include <misc/Computations.h>
#include <shapes/Sphere.h>
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
        REQUIRE(rt::stripeAt(pattern, util::Tuple::point(0, 0, 0)) == white);
        REQUIRE(rt::stripeAt(pattern, util::Tuple::point(0, 1, 0)) == white);
        REQUIRE(rt::stripeAt(pattern, util::Tuple::point(0, 2, 0)) == white);
      }
    }
    WHEN("A stripe pattern is constant in z")
    {
      auto pattern = rt::StripePattern(white, black);
      THEN("")
      {
        REQUIRE(rt::stripeAt(pattern, util::Tuple::point(0, 0, 0)) == white);
        REQUIRE(rt::stripeAt(pattern, util::Tuple::point(0, 0, 1)) == white);
        REQUIRE(rt::stripeAt(pattern, util::Tuple::point(0, 0, 2)) == white);
      }
    }
    WHEN("A stripe pattern alternates in x")
    {
      auto pattern = rt::StripePattern(white, black);
      THEN("")
      {
        REQUIRE(rt::stripeAt(pattern, util::Tuple::point(0, 0, 0)) == white);
        REQUIRE(rt::stripeAt(pattern, util::Tuple::point(0.9, 0, 0)) == white);
        REQUIRE(rt::stripeAt(pattern, util::Tuple::point(1, 0, 0)) == black);
        REQUIRE(rt::stripeAt(pattern, util::Tuple::point(-0.1, 0, 0)) == black);
        REQUIRE(rt::stripeAt(pattern, util::Tuple::point(-1, 0, 0)) == black);
        REQUIRE(rt::stripeAt(pattern, util::Tuple::point(-1.1, 0, 0)) == white);
      }
    }
    WHEN("Stripes with an object transformation")
    {
      auto sphere = rt::Sphere();
      sphere.setTransform(util::Matrixd::scaling(2, 2, 2));
      auto pattern = rt::StripePattern(white,black);
      auto c = rt::stripeAtObject(pattern, sphere, util::Tuple::point(1.5, 0, 0));
      THEN("")
      {
        REQUIRE(c == white);
      }
    }
    WHEN("Stripes with pattern transformation")
    {
      auto sphere = rt::Sphere();
      auto pattern = rt::StripePattern(white,black);
      pattern.setTransform(util::Matrixd::scaling(2,2,2));
      auto c = rt::stripeAtObject(pattern, sphere, util::Tuple::point(1.5, 0, 0));
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
      pattern.setTransform(util::Matrixd::translation(0.5,0,0));
      auto c = rt::stripeAtObject(pattern, sphere, util::Tuple::point(2.5, 0, 0));
      THEN("")
      {
        REQUIRE(c == white);
      }
    }
  }
}

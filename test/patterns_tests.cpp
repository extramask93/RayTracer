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
#include <patterns/UVCheckers.h>
#include <patterns/TextureMap.h>
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
SCENARIO("Checker pattern in 2D") {
  GIVEN("") {
    auto checkers = rt::UVCheckers(2,2,util::Color(0,0,0), util::Color(1,1,1));
    auto examples = std::vector<std::tuple<double,double,util::Color>> {
      {0.0, 0.0, util::Color::BLACK},
      {0.5, 0.0, util::Color::WHITE},
      {0.0, 0.5, util::Color::WHITE},
      {0.5, 0.5, util::Color::BLACK},
      {1.0, 1.0, util::Color::BLACK},
    };
    const auto [u,v, expected] = GENERATE_COPY(from_range(examples));
    WHEN("") {
      auto color = checkers.uvPatternAt(u,v);
      THEN("") {
        REQUIRE(color == expected);
      }
    }
  }
}
SCENARIO("Using spherical mapping on a 3D point") {
  const auto examples = std::vector<std::tuple<util::Tuple, double, double>> {
    {util::Tuple::point(0,0,-1), 0.0, 0.5},
    {util::Tuple::point(1,0,0), 0.25, 0.5},
    {util::Tuple::point(0,0,1), 0.5, 0.5},
    {util::Tuple::point(-1,0,0), 0.75, 0.5},
    {util::Tuple::point(0,1,0), 0.5, 1.0},
    {util::Tuple::point(0,-1,0), 0.5, 0.0},
    {util::Tuple::point(sqrt(2)/2,sqrt(2)/2,0), 0.25, 0.75},
  };
  GIVEN("") {
    const auto [p,uex,vex] = GENERATE_COPY(from_range(examples));
    WHEN(""){
      auto [u,v] = rt::spherical_map(p);
      THEN("") {
        REQUIRE(u == uex);
        REQUIRE(v == vex);
      }
    }
  }
}
SCENARIO("Using a texture map pattern with a spherical map") {
  GIVEN("") {
    auto checkers = rt::UVCheckers(16,8,util::Color::BLACK,util::Color::WHITE);
    auto pattern = rt::TextureMap(&checkers, rt::spherical_map);
    auto examples = std::vector<std::tuple<util::Tuple, util::Color>> {
      {util::Tuple::point(0.4315,0.4670,0.7719), util::Color::WHITE},
      {util::Tuple::point(-0.9654, 0.2552, -0.0534), util::Color::BLACK},
      {util::Tuple::point(0.1039, 0.7090, 0.6975), util::Color::WHITE},
      {util::Tuple::point(-0.4986, -0.7856, -0.3663), util::Color::BLACK},
      {util::Tuple::point(-0.0317, -0.9395, 0.3411), util::Color::BLACK},
      {util::Tuple::point(0.4809, -0.7721, 0.4154), util::Color::BLACK},
      {util::Tuple::point(0.0285, -0.9612, -0.2745), util::Color::BLACK},
      {util::Tuple::point(-0.5734, -0.2162, -0.7903), util::Color::WHITE},
      {util::Tuple::point(0.7688, -0.1470, 0.6223), util::Color::BLACK},
      {util::Tuple::point(-0.7652, 0.2175, 0.6060), util::Color::BLACK},
    };
    const auto [point,color] = GENERATE_COPY(from_range(examples));
    THEN("") {
      REQUIRE(pattern.patternAt(point) == color);
    }
  }
}
SCENARIO("Using planar mapping on a 3D point") {
  const auto examples = std::vector<std::tuple<util::Tuple, double, double>> {
    {util::Tuple::point(0.25,0,0.5), 0.25, 0.5},
    {util::Tuple::point(0.25,0,-0.25), 0.25, 0.75},
    {util::Tuple::point(0.25,0.5,-0.25), 0.25, 0.75},
    {util::Tuple::point(1.25,0,0.5), 0.25, 0.5},
    {util::Tuple::point(0.25,0,-1.75), 0.25, 0.25},
    {util::Tuple::point(1,0,-1), 0.0, 0.0},
    {util::Tuple::point(0,0,0), 0.0, 0.0},
  };
  GIVEN("") {
    const auto [p,uex,vex] = GENERATE_COPY(from_range(examples));
    WHEN(""){
      auto [u,v] = rt::planar_map(p);
      THEN("") {
        REQUIRE(u == uex);
        REQUIRE(v == vex);
      }
    }
  }
}

SCENARIO("Using cylindircal mapping on a 3D point") {
  const auto examples = std::vector<std::tuple<util::Tuple, double, double>> {
    {util::Tuple::point(0, 0, -1), 0.0, 0.0},
    {util::Tuple::point(0, 0.5, -1), 0.0, 0.5},
    {util::Tuple::point(0, 1, -1), 0.0, 0.0},
    {util::Tuple::point(0.70711, 0.5, -0.70711), 0.125, 0.5},
    {util::Tuple::point(1, 0.5, 0), 0.25, 0.5},
    {util::Tuple::point(0.70711, 0.5, 0.70711), 0.375, 0.5},
    {util::Tuple::point(0, -0.25, 1), 0.5, 0.75},
    {util::Tuple::point(-0.70711, 0.5, 0.70711), 0.625, 0.5},
    {util::Tuple::point(-1, 1.25, 0), 0.75, 0.25},
    {util::Tuple::point(-0.70711, 0.5, -0.70711), 0.875, 0.5},
  };
  GIVEN("") {
    const auto [p,uex,vex] = GENERATE_COPY(from_range(examples));
    WHEN(""){
      auto [u,v] = rt::cylindrical_map(p);
      THEN("") {
        REQUIRE(u == uex);
        REQUIRE(v == vex);
      }
    }
  }
}

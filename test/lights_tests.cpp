//
// Created by damian on 08.07.2020.
//
#include <catch2/catch.hpp>
#include <Color.h>
#include <lights/PointLight.h>
SCENARIO("A point light has a position and intensity") {
  GIVEN("Intensity") {
    auto intensity  = util::Color(1,1,1);
    AND_GIVEN("Position of the light") {
      auto position = util::Tuple::point(0,0,0);
      WHEN("Creating a light") {
        auto light = rt::PointLight(position,intensity);
        THEN("") {
          REQUIRE(light.position() == position);
          REQUIRE(light.intensity() == intensity);
        }
      }
    }
  }
}
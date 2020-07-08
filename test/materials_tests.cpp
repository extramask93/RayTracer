//
// Created by damian on 08.07.2020.
//
#include <catch2/catch.hpp>
#include <Color.h>
#include <Tuple.h>
#include <materials/Material.h>
SCENARIO("The default material") {
  GIVEN("Material") {
    auto  m= rt::Material();
    THEN("") {
      REQUIRE(m.color() == util::Color(1,1,1));
      REQUIRE(m.ambient() == 0.1);
      REQUIRE(m.diffuse() == 0.9);
      REQUIRE(m.specular() == 0.9);
      REQUIRE(m.shininess() == 200.0);
    }
  }
}

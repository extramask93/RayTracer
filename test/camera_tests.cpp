//
// Created by damian on 11.07.2020.
//
#include <catch2/catch.hpp>
#include <Matrix.h>
#include <camera/Camera.h>
#include <misc/Computations.h>

SCENARIO("Constructing a camera")
{
  GIVEN("")
  {
    unsigned hsize = 160;
    unsigned vsize = 120;
    double fieldOfView = M_PI / 2;
    WHEN("Creating camera")
    {
      auto c = rt::Camera(hsize, vsize, fieldOfView);
      THEN("")
      {
        REQUIRE(c.hsize() == 160);
        REQUIRE(c.vsize() == 120);
        REQUIRE(c.fieldOfView() == M_PI / 2);
        REQUIRE(c.transform() == util::Matrixd::Identity(4));
      }
    }
  }
}

SCENARIO("The pixel size for a horizontal canvas")
{
  GIVEN("")
  {
    auto c = rt::Camera(200, 125, M_PI/2);
    THEN("")
    {
      REQUIRE(c.pixelSize() == Approx(0.01));
    }
  }
}
SCENARIO("Constructing a ray through the center of the canvas")
{
  GIVEN("")
  {
    auto c = rt::Camera(201, 101, M_PI/2);
    WHEN("")
    {
      auto r = rt::rayForPixel(c,100,50);
      THEN("")
      {
        REQUIRE(r.origin() == util::Tuple::point(0,0,0));
        REQUIRE(r.direction() == util::Tuple::vector(0,0,-1));
      }
    }
  }
}
SCENARIO("Constructing a ray through a corner of the canvas")
{
  GIVEN("")
  {
    auto c = rt::Camera(201, 101, M_PI/2);
    WHEN("")
    {
      auto r = rt::rayForPixel(c,0,0);
      THEN("")
      {
        REQUIRE(r.origin() == util::Tuple::point(0,0,0));
        REQUIRE(r.direction() == util::Tuple::vector(0.66519,0.33259,-0.66851));
      }
    }
  }
}
SCENARIO("Constructing a ray when camera is transformed")
{
  GIVEN("")
  {
    auto c = rt::Camera(201, 101, M_PI/2);
    c.setTransform(util::Matrixd::rotation_y(M_PI/4) * util::Matrixd::translation(0,-2,5));
    WHEN("")
    {
      auto r = rt::rayForPixel(c,100,50);
      THEN("")
      {
        REQUIRE(r.origin() == util::Tuple::point(0,2,-5));
        REQUIRE(r.direction() == util::Tuple::vector(sqrt(2)/2,0,-sqrt(2)/2));
      }
    }
  }
}
SCENARIO("Rendering a world with a camera") {
  GIVEN("") {
    auto w  = rt::World::defaultWorld();
    auto c = rt::Camera(11,11,M_PI/2);
    auto from = util::Tuple::point(0,0,-5);
    auto to = util::Tuple::point(0,0,0);
    auto up = util::Tuple::vector(0,1,0);
    c.setTransform(rt::viewTransformation(from,to,up));
    WHEN("") {
      auto image = rt::render(c,*w);
      THEN("") {
        REQUIRE(image(5,5) == util::Color(0.38066,0.47583,0.2855));
      }
    }
  }
}

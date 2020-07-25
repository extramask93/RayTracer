//
// Created by damian on 23.07.2020.
//

#include <catch2/catch.hpp>
#include <Tuple.h>
#include <misc/AABB.h>
#include <shapes/Sphere.h>
#include <shapes/Plane.h>
#include <shapes/Cube.h>
#include <shapes/Cylinder.h>
#include <shapes/Group.h>

SCENARIO("Creating a bounding box")
{
  GIVEN("")
  {
    auto aabb = rt::AABB(util::Tuple::point(-1, -1, -1), util::Tuple::point(1, 1, 1));
    THEN("")
    {
      REQUIRE(aabb.min() == util::Tuple::point(-1, -1, -1));
      REQUIRE(aabb.max() == util::Tuple::point(1, 1, 1));
    }
  }
}
SCENARIO("Creating empty bounding box")
{
  GIVEN("")
  {
    auto aabb = rt::AABB();
    WHEN("AABB is not modified")
    {
      THEN("")
      {
        REQUIRE(aabb.max().x() == Approx(math::ninf<>));
        REQUIRE(aabb.max().y() == Approx(math::ninf<>));
        REQUIRE(aabb.max().z() == Approx(math::ninf<>));
        REQUIRE(aabb.min().x() == Approx(math::inf<>));
        REQUIRE(aabb.min().y() == Approx(math::inf<>));
        REQUIRE(aabb.min().z() == Approx(math::inf<>));
      }
    }
  }
}
SCENARIO("Expanding empty bounding box by points")
{
  GIVEN("")
  {
    auto aabb = rt::AABB();
    WHEN("Adding points")
    {
      aabb.add(util::Tuple::point(2, 2, 2));
      aabb.add(util::Tuple::point(-2, -2, -2));
      THEN("")
      {
        REQUIRE(aabb.max() == util::Tuple::point(2, 2, 2));
        REQUIRE(aabb.min() == util::Tuple::point(-2, -2, -2));
      }
    }
  }
}
SCENARIO("Expanding empty bounding box by another box")
{
  GIVEN("")
  {
    auto aabb1 = rt::AABB(util::Tuple::point(-1, -1, -1), util::Tuple::point(1, 1, 1));
    auto aabb2 = rt::AABB(util::Tuple::point(0, 0, 0), util::Tuple::point(3, 3, 3));
    WHEN("Adding")
    {
      auto aabb = aabb1.add(aabb2);
      THEN("")
      {
        REQUIRE(aabb.max() == util::Tuple::point(3, 3, 3));
        REQUIRE(aabb.min() == util::Tuple::point(-1, -1, -1));
      }
    }
  }
}
SCENARIO("Shape return it's bounding box")
{
  GIVEN("")
  {
    auto sphere = rt::Sphere();
    auto result = rt::AABB(util::Tuple::point(-1, -1, -1), util::Tuple::point(1, 1, 1));
    auto aabb = sphere.bounds();
    THEN("")
    {
      REQUIRE(aabb == result);
    }
  }
}
SCENARIO("Plane return it's bounding box")
{
  GIVEN("")
  {
    auto sphere = rt::Plane();
    auto result = rt::AABB(
      util::Tuple::point(math::ninf<>, 0, math::ninf<>),
      util::Tuple::point(math::inf<>, 0, math::inf<>));
    auto aabb = sphere.bounds();
    THEN("")
    {
      REQUIRE(aabb.max() == result.max());
    }
  }
}

SCENARIO("Cube return it's bounding box")
{
  GIVEN("")
  {
    auto sphere = rt::Cube();
    auto result = rt::AABB(
      util::Tuple::point(-1, -1, -1),
      util::Tuple::point(1, 1, 1));
    auto aabb = sphere.bounds();
    THEN("")
    {
      REQUIRE(aabb.max() == result.max());
    }
  }
}

SCENARIO("boundless cylinder return it's bounding box")
{
  GIVEN("")
  {
    auto sphere = rt::Cylinder();
    auto result = rt::AABB(
      util::Tuple::point(-1, math::ninf<>, -1),
      util::Tuple::point(1, math::inf<>, 1));
    auto aabb = sphere.bounds();
    THEN("")
    {
      REQUIRE(aabb == result);
    }
  }
}

SCENARIO("Transforming the bounding box")
{
  GIVEN("")
  {
    auto aabb1 = rt::AABB(util::Tuple::point(-1, -1, -1), util::Tuple::point(1, 1, 1));
    auto transform = util::Matrixd::scaling(2, 3, 4);
    auto aabb2 = aabb1.transform(transform);
    auto result = rt::AABB(
      util::Tuple::point(-2, -3, -4),
      util::Tuple::point(2, 3, 4));
    THEN("")
    {
      REQUIRE(aabb2 == result);
    }
  }
}
SCENARIO("Bounding box of untransformed group")
{
  GIVEN("")
  {
    auto sphere = std::make_shared<rt::Sphere>();
    auto cube = std::make_shared<rt::Cube>();
    auto group = std::make_shared<rt::Group>();
    auto result = rt::AABB(util::Tuple::point(-1, -1, -1), util::Tuple::point(3, 1, 1));
    group->addChild(sphere).addChild(cube);
    sphere->setTransform(util::Matrixd::translation(2, 0, 0));
    WHEN("")
    {
      auto bounds = group->bounds();
      THEN("")
      {
        REQUIRE(bounds == result);
      }
    }
  }
}
SCENARIO("Bounding box of transformed group")
{
  GIVEN("")
  {
    auto sphere = std::make_shared<rt::Sphere>();
    auto cube = std::make_shared<rt::Cube>();
    auto group = std::make_shared<rt::Group>();
    auto result = rt::AABB(util::Tuple::point(-sqrt(2), -sqrt(2), -1), util::Tuple::point(sqrt(2), sqrt(2), 1));
    group->addChild(sphere).addChild(cube);
    //sphere->setTransform(util::Matrixd::translation(2,0,0));
    group->setTransform(util::Matrixd::rotation_z(45 * math::pi<> / 180));
    WHEN("")
    {
      auto bounds = group->parentSpaceBounds();
      THEN("")
      {
        REQUIRE(bounds == result);
      }
    }
  }
}
SCENARIO("Check if ray intersectes a group")
{
  GIVEN("")
  {
    auto sphere = std::make_shared<rt::Sphere>();
    auto cube = std::make_shared<rt::Cube>();
    auto group = std::make_shared<rt::Group>();
    //auto result = rt::AABB(util::Tuple::point(-sqrt(2), -sqrt(2), -1), util::Tuple::point(sqrt(2), sqrt(2), 1));
    group->addChild(sphere).addChild(cube);
    group->setTransform(util::Matrixd::rotation_z(45 * math::pi<> / 180));
    auto ray = rt::Ray(util::Tuple::point(-3,0,0), util::Tuple::vector(1,0,0));
    THEN("") {
      REQUIRE(group->bounds().intersect(ray) == true);
    }
  }
}
SCENARIO("Check if ray does intersect a group")
{
  GIVEN("")
  {
    auto sphere = std::make_shared<rt::Sphere>();
    auto cube = std::make_shared<rt::Cube>();
    auto group = std::make_shared<rt::Group>();
    //auto result = rt::AABB(util::Tuple::point(-sqrt(2), -sqrt(2), -1), util::Tuple::point(sqrt(2), sqrt(2), 1));
    group->addChild(sphere).addChild(cube);
    group->setTransform(util::Matrixd::rotation_z(45 * math::pi<> / 180));
    auto ray = rt::Ray(util::Tuple::point(-4,0,0), util::Tuple::vector(0,3,0));
    THEN("") {
      REQUIRE(group->bounds().intersect(ray) == false);
    }
  }
}

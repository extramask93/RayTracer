//
// Created by damian on 29.05.2020.
//

#include <catch2/catch.hpp>
#include <Color.h>
#include <Canvas.h>
SCENARIO("Creating a canvas")
{
  GIVEN("Width and height of canvas")
  {
    auto canvas = util::Canvas(10,20);
    THEN("canvas width = 10")
    {
      REQUIRE(canvas.width() == 10);
    }
    AND_THEN("canvas height =20"){
      REQUIRE(canvas.height() == 20);
    }
    AND_THEN("Every pixel is black") {
      for(const auto &pixel : canvas) {
        REQUIRE(pixel == util::Color(0,0,0));
      }
    }
  }
}
SCENARIO("Writing pixels to canvas")
{
  GIVEN("c = Canvas(10,20)")
  {
    auto canvas = util::Canvas(10,20);
    AND_GIVEN("red = Color(1,0,0)")
    {
      auto red = util::Color(1,0,0);
      WHEN("canvas.setPixel(2,3,red)")
      {
        canvas(2,3) = red;
        THEN("canvas(2,3) == red")
        {
          REQUIRE(canvas(2,3) == red);
        }
      }
    }
}
}

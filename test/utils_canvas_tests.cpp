//
// Created by damian on 29.05.2020.
//

#include <catch2/catch.hpp>
#include <Color.h>
#include <Canvas.h>
#include <CanvasPrinter.h>
#include <fstream>
SCENARIO("Creating a canvas")
{
  GIVEN("Width and height of canvas")
  {
    auto canvas = util::Canvas(10, 20);
    THEN("canvas width = 10")
    {
      REQUIRE(canvas.width() == 10);
    }
    AND_THEN("canvas height =20")
    {
      REQUIRE(canvas.height() == 20);
    }
    AND_THEN("Every pixel is black")
    {
      for (const auto &pixel : canvas) {
        REQUIRE(pixel == util::Color(0, 0, 0));
      }
    }
  }
}
SCENARIO("Writing pixels to canvas")
{
  GIVEN("c = Canvas(10,20)")
  {
    auto canvas = util::Canvas(10, 20);
    AND_GIVEN("red = Color(1,0,0)")
    {
      auto red = util::Color(1, 0, 0);
      WHEN("canvas.setPixel(2,3,red)")
      {
        canvas(2, 3) = red;
        THEN("canvas(2,3) == red")
        {
          REQUIRE(canvas(2, 3) == red);
        }
      }
    }
  }
}
SCENARIO("Construction the PPM header")
{
  GIVEN("c = Canvas(5,3)")
  {
    auto canvas = util::Canvas(5, 3);
    WHEN("ppm = canvastoppm(c)")
    {
      util::CanvasPrinter printer;
      auto currentPath = std::filesystem::current_path();
      currentPath += "test.ppm";
      printer.printToPPM(currentPath, canvas);
      THEN("Lines of ppm are")
      {
        std::ifstream file(currentPath);
        std::string buffer;
        std::getline(file, buffer);
        REQUIRE(buffer == "P3");
        std::getline(file, buffer);
        REQUIRE(buffer == "5");
        std::getline(file, buffer);
        REQUIRE(buffer == "3");
        std::getline(file, buffer);
        REQUIRE(buffer == "255");
      }
    }
  }
}
SCENARIO("Constructing the ppm pixel data")
{
  GIVEN("c = Canvas(5,3)")
  {
    auto canvas = util::Canvas(5, 3);
    AND_GIVEN("c1 = Color(1.5,0,0")
    {
      auto c1 = util::Color(1.5, 0, 0);
      AND_GIVEN("c2 = Color(0,0.5,0)")
      {
        auto c2 = util::Color(0, 0.5, 0);
        AND_GIVEN("c3 = Color(-0.5,0,1)")
        {
          auto c3 = util::Color(-0.5, 0, 1);
          WHEN("")
          {
            canvas(0, 0) = c1;
            AND_WHEN("")
            {
              canvas(2, 1) = c2;
              AND_WHEN("")
              {
                canvas(4, 2) = c3;
                AND_WHEN("")
                {
                  util::CanvasPrinter printer;
                  auto currentPath = std::filesystem::current_path();
                  currentPath += "test.ppm";
                  printer.printToPPM(currentPath, canvas);
                  THEN("lines 4-6 of the ppm file are")
                  {
                    const std::string result =
                      "255 0 0 0 0 0 0 0 0 0 0 0 0 0 0 "
                      "0 0 0 0 0 0 0 128 0 0 0 0 0 0 0 "
                      "0 0 0 0 0 0 0 0 0 0 0 0 0 0 255 ";
                    std::ifstream file(currentPath);
                    std::stringstream buffer;
                    for (int currLineNumber = 0; currLineNumber < 4; ++currLineNumber) {
                      if (file.ignore(std::numeric_limits<int>::max(), file.widen('\n'))) {
                        //just skipping the line
                      }
                    }
                    buffer << file.rdbuf();
                    auto s = buffer.str();
                    std::transform(s.begin(), s.end(), s.begin(), [](const char &c) { if(c == '\n') {return ' ';} else {return c;} });
                    REQUIRE(s == result);
                  }
                }
              }
            }
          }
        }
      }
    }
  }
}

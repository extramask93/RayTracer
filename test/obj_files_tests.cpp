//
// Created by damian on 26.07.2020.
//
#include <catch2/catch.hpp>
#include <parser/ObjParser.h>
#include <shapes/Group.h>
#include <shapes/Triangle.h>
#include <sstream>
#include <Tuple.h>
#include <shapes/SmoothTriangle.h>
SCENARIO("Ignoring unrecognized lines") {
  GIVEN("")
  {
    std::stringstream ss;
    ss <<"There was a young lady names Bright \n"
          "who traveled much faster than light \n"
          "She set out one day \n"
          "in a relative way\n"
          "and came back the previous night";
    WHEN("") {
      auto parser = rt::ObjParser::fromStream(ss);
      THEN("") {
        REQUIRE(parser.linesIgnored() == 5);
      }
    }
  }
}
SCENARIO("Vertex records") {
  GIVEN("") {
    auto ss = std::stringstream();
    ss <<"\n"
          "v -1 1 0\n"
          "v -1.0000 0.50000 0.0000\n"
          "v 1 0 0\n"
          "v 1 1 0\n";
    WHEN("") {
      auto parser = rt::ObjParser::fromStream(ss);
      THEN("") {
        REQUIRE(parser.vertices()[1] == util::Tuple::point(-1,1,0));
        REQUIRE(parser.vertices()[2] == util::Tuple::point(-1,0.5,0));
        REQUIRE(parser.vertices()[3] == util::Tuple::point(1,0,0));
        REQUIRE(parser.vertices()[4] == util::Tuple::point(1,1,0));
      }
    }
  }
}
SCENARIO("Parsing triangle faces") {
  GIVEN("") {
    auto ss = std::stringstream();
    ss << "\n"
          "v -1 1 0\n"
          "v -1.0000 0.00000 0.0000\n"
          "v 1 0 0\n"
          "v 1 1 0\n"
          "\n"
          "f 1 2 3\n"
          "f 1 3 4\n";
    WHEN("") {
      auto parser = rt::ObjParser::fromStream(ss);
      auto g = parser.defaultGroup();
      auto t1 = std::dynamic_pointer_cast<rt::Triangle>(g->children()[0]);
      auto t2 =std::dynamic_pointer_cast<rt::Triangle>(g->children()[1]);
      THEN("") {
        REQUIRE(t1->p1() == parser.vertices()[1]);
        REQUIRE(t1->p2() == parser.vertices()[2]);
        REQUIRE(t1->p3() == parser.vertices()[3]);
        REQUIRE(t2->p1() == parser.vertices()[1]);
        REQUIRE(t2->p2() == parser.vertices()[3]);
        REQUIRE(t2->p3() == parser.vertices()[4]);

      }
    }
  }
}
SCENARIO("Triangulating polygons") {
  GIVEN("") {
    auto ss = std::stringstream();
    ss << "\n"
          "v -1 1 0\n"
          "v -1.0000 0.00000 0.0000\n"
          "v 1 0 0\n"
          "v 1 1 0\n"
          "v 0 2 0\n"
          "\n"
          "f 1 2 3 4 5\n";
    WHEN("") {
      auto parser = rt::ObjParser::fromStream(ss);
      auto g = parser.defaultGroup();
      auto t1 = std::dynamic_pointer_cast<rt::Triangle>(g->children()[0]);
      auto t2 =std::dynamic_pointer_cast<rt::Triangle>(g->children()[1]);
      auto t3 =std::dynamic_pointer_cast<rt::Triangle>(g->children()[2]);
      THEN("") {
        REQUIRE(t1->p1() == parser.vertices()[1]);
        REQUIRE(t1->p2() == parser.vertices()[2]);
        REQUIRE(t1->p3() == parser.vertices()[3]);
        REQUIRE(t2->p1() == parser.vertices()[1]);
        REQUIRE(t2->p2() == parser.vertices()[3]);
        REQUIRE(t2->p3() == parser.vertices()[4]);
        REQUIRE(t3->p1() == parser.vertices()[1]);
        REQUIRE(t3->p2() == parser.vertices()[4]);
        REQUIRE(t3->p3() == parser.vertices()[5]);

      }
    }
  }
}
SCENARIO("Triangles in groups") {
  GIVEN("") {
    auto ss = std::stringstream();
    ss<<"v -1 1 0\n"
          "v -1 0 0\n"
          "v 1 0 0\n"
          "v 1 1 0\n"
          "\n"
          "g FirstGroup\n"
          "f 1 2 3\n"
          "g SecondGroup\n"
          "f 1 3 4";
    auto parser = rt::ObjParser::fromStream(ss);
    auto g1 = parser.groups()["FirstGroup"];
    auto g2 = parser.groups()["SecondGroup"];
    auto t1 = std::dynamic_pointer_cast<rt::Triangle>(g1->children()[0]);
    auto t2 = std::dynamic_pointer_cast<rt::Triangle>(g2->children()[0]);
    THEN("") {
      REQUIRE(t1->p1() == parser.vertices()[1]);
      REQUIRE(t1->p2() == parser.vertices()[2]);
      REQUIRE(t1->p3() == parser.vertices()[3]);
      REQUIRE(t2->p1() == parser.vertices()[1]);
      REQUIRE(t2->p2() == parser.vertices()[3]);
      REQUIRE(t2->p3() == parser.vertices()[4]);
    }
  }
}
SCENARIO("Converting an OBJ Model to a Group") {
  GIVEN("") {
    auto ss = std::stringstream();
    ss<<"v -1 1 0\n"
        "v -1 0 0\n"
        "v 1 0 0\n"
        "v 1 1 0\n"
        "\n"
        "g FirstGroup\n"
        "f 1 2 3\n"
        "g SecondGroup\n"
        "f 1 3 4";
    auto parser = rt::ObjParser::fromStream(ss);
    auto g = parser.objToGroup();
    THEN("") {
      REQUIRE(g->children().size() ==3);
   }
  }
}

SCENARIO("Vertex normal records") {
  GIVEN("") {
    auto ss = std::stringstream();
    ss<<"vn 0 0 1\n"
          "vn 0.707 0 -0.707\n"
          "vn 1 2 3";
    auto parser = rt::ObjParser::fromStream(ss);
    THEN("") {
      REQUIRE(parser.normals()[1] == util::Tuple::vector(0,0,1));
      REQUIRE(parser.normals()[2] == util::Tuple::vector(0.707,0,-0.707));
      REQUIRE(parser.normals()[3] == util::Tuple::vector(1,2,3));
    }
  }
}

SCENARIO("Faces with normals") {
  GIVEN("") {
    auto ss = std::stringstream();
    ss<<"v 0 1 0\n"
        "v -1 0 0\n"
        "v 1 0 0\n"
        "\n"
          "vn -1 0 0\n"
          "vn 1 0 0\n"
          "vn 0 1 0\n"
        "f 1//3 2//1 3//2\n"
        "f 1/0/3 2/102/1 3/14/2";
    auto parser = rt::ObjParser::fromStream(ss);
    auto g = parser.defaultGroup();
    auto t1 = std::dynamic_pointer_cast<rt::SmoothTriangle>(g->children()[0]);
    auto t2 = std::dynamic_pointer_cast<rt::SmoothTriangle>(g->children()[1]);
    THEN("") {
      REQUIRE(t1->p1() == parser.vertices()[1]);
      REQUIRE(t1->p2() == parser.vertices()[2]);
      REQUIRE(t1->p3() == parser.vertices()[3]);
      REQUIRE(t1->n1() == parser.normals()[3]);
      REQUIRE(t1->n2() == parser.normals()[1]);
      REQUIRE(t1->n3() == parser.normals()[2]);
      REQUIRE(t2->p1() == t1->p1());
      REQUIRE(t2->p2() == t1->p2());
      REQUIRE(t2->p3() == t1->p3());
      REQUIRE(t2->n1() == t1->n1());
      REQUIRE(t2->n2() == t1->n2());
      REQUIRE(t2->n3() == t1->n3());
    }
  }
}

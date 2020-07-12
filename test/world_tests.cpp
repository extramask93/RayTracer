//
// Created by damian on 09.07.2020.
//
#include <catch2/catch.hpp>
#include <world/World.h>
#include <lights/PointLight.h>
#include <Tuple.h>
#include <Color.h>
#include <shapes/Sphere.h>
#include <misc/Computations.h>
#include <misc/Shader.h>
SCENARIO("Creating a world") {
  GIVEN("A world") {
    auto w = rt::World();
    THEN("") {
      REQUIRE(w.lights().size() == 0);
      REQUIRE(w.lights().size() == 0);
    }
  }
}
SCENARIO("The default world") {
  GIVEN("A light and spheres") {
    WHEN("Getting default values") {
      auto w = rt::World::defaultWorld();
      THEN("") {
        REQUIRE(w->shapes().size() == 2);
        REQUIRE(w->lights().size() ==1);
      }
    }
  }
}
SCENARIO("Intersect a world with a ray"){
  GIVEN("Default world") {
    auto w = rt::World::defaultWorld();
    AND_GIVEN("A ray") {
      auto r = rt::Ray(util::Tuple::point(0,0,-5), util::Tuple::vector(0,0,1));
      WHEN("Intersecting the world") {
        auto xs = w->intersect(r);
        THEN("") {
          REQUIRE(xs.size() == 4);
          REQUIRE(xs[0].t() == 4);
          REQUIRE(xs[1].t() == 4.5);
          REQUIRE(xs[2].t() == 5.5);
          REQUIRE(xs[3].t() == 6);
        }
      }
    }
  }
}
SCENARIO("Shading an instersection") {
  GIVEN("") {
    auto w = rt::World::defaultWorld();
    auto r = rt::Ray(util::Tuple::point(0,0,-5), util::Tuple::vector(0,0,1));
    auto shape = w->shapes()[0].get();
    auto i  = rt::Intersection(4,shape);
    WHEN("") {
      auto comps=rt::prepareComputations(i,r);
      auto c = rt::Shader::shadeHit(*w,comps);
      THEN("") {
        REQUIRE(c == util::Color(0.38066,0.47583,0.2855));
      }
    }
  }
}
SCENARIO("Shading an instersection from the inside") {
  GIVEN("") {
    auto w = rt::World::defaultWorld();
    w->lights()[0].reset(new rt::PointLight(util::Tuple::point(0,0.25,0), util::Color(1,1,1)));
    auto r = rt::Ray(util::Tuple::point(0,0,0), util::Tuple::vector(0,0,1));
    auto shape = w->shapes()[1].get();
    auto i  = rt::Intersection(0.5,shape);
    WHEN("") {
      auto comps=rt::prepareComputations(i,r);
      auto c = rt::Shader::shadeHit(*w,comps);
      THEN("") {
        REQUIRE(c == util::Color(0.90498,0.90498,0.90498));
      }
    }
  }
}
SCENARIO("The color when a ray misses") {
  GIVEN("") {
    auto w = rt::World::defaultWorld();
    auto r = rt::Ray(util::Tuple::point(0,0,-5),util::Tuple::vector(0,1,0));
    WHEN("") {
      auto c = rt::colorAt(*w,r);
      THEN("") {
        REQUIRE(c == util::Color(0,0,0));
      }
    }
  }
}
SCENARIO("The color when a ray hits") {
  GIVEN("") {
    auto w = rt::World::defaultWorld();
    auto r = rt::Ray(util::Tuple::point(0,0,-5),util::Tuple::vector(0,0,1));
    WHEN("") {
      auto c = rt::colorAt(*w,r);
      THEN("") {
        REQUIRE(c == util::Color(0.38066,0.47583,0.2855));
      }
    }
  }
}
SCENARIO("The color with an intersection behind the ray") {
  GIVEN("") {
    auto w = rt::World::defaultWorld();
    auto outer = w->shapes()[0].get();
    auto material = outer->material();
    material.setAmbient(1);
    outer->setMaterial(material);
    auto inner = w->shapes()[1].get();
    material = inner->material();
    material.setAmbient(1);
    inner->setMaterial(material);
    auto r = rt::Ray(util::Tuple::point(0,0,0.75),util::Tuple::vector(0,0,-1));
    WHEN("") {
      auto c = rt::colorAt(*w,r);
      THEN("") {
        REQUIRE(c == inner->material().color());
      }
    }
  }
}
SCENARIO("There is no shadow when nothing is collinear with point and light") {
  GIVEN("") {
    auto w = rt::World::defaultWorld();
    auto p = util::Tuple::point(0,10,0);
    THEN("") {
      REQUIRE(rt::isShadowed(*w,p) == false);
    }
  }
}

SCENARIO("The shadow when an object is between the point and the light") {
  GIVEN("") {
    auto w = rt::World::defaultWorld();
    auto p = util::Tuple::point(10,-10,10);
    THEN("") {
      REQUIRE(rt::isShadowed(*w,p) == true);
    }
  }
}
SCENARIO("There is no shadow when an object is behind the light") {
  GIVEN("") {
    auto w = rt::World::defaultWorld();
    auto p = util::Tuple::point(-20,20,-20);
    THEN("") {
      REQUIRE(rt::isShadowed(*w,p) == false);
    }
  }
}

SCENARIO("There is no shadow when an object is behind the point") {
  GIVEN("") {
    auto w = rt::World::defaultWorld();
    auto p = util::Tuple::point(-2,2,-2);
    THEN("") {
      REQUIRE(rt::isShadowed(*w,p) == false);
    }
  }
}
SCENARIO("shadeHit is given an intersection in shadow") {
  GIVEN("") {
    auto world = rt::World();
    world.lights().emplace_back(std::make_unique<rt::PointLight>(util::Tuple::point(0,0,-10),util::Color(1,1,1)));
    world.shapes().emplace_back(std::make_unique<rt::Sphere>());
    world.shapes().emplace_back(std::make_unique<rt::Sphere>());
    world.shapes()[1].get()->setTransform(util::Matrixd::translation(0,0,10));
    auto r = rt::Ray(util::Tuple::point(0,0,5), util::Tuple::vector(0,0,1));
    auto i  = rt::Intersection(4,world.shapes()[1].get());
    auto comps = rt::prepareComputations(i,r);
    auto c = rt::Shader::shadeHit(world,comps);
    THEN("") {
      REQUIRE(c == util::Color(0.1,0.1,0.1));
    }
  }
}

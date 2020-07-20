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
#include <shapes/Plane.h>
#include <patterns/TestPattern.h>
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
      REQUIRE(rt::isShadowed(*w, p));
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

SCENARIO("The reflected color for a nonreflective material") {
  GIVEN("") {
    auto world = rt::World::defaultWorld();
    world->shapes()[1].get()->material().setAmbient(1);
    auto r = rt::Ray(util::Tuple::point(0,0,0), util::Tuple::vector(0,0,1));
    auto i  = rt::Intersection(1,world->shapes()[1].get());
    auto comps = rt::prepareComputations(i,r);
    auto c = rt::reflectedColor(*world,comps,2);
    THEN("") {
      REQUIRE(c == util::Color(0,0,0));
    }
  }
}

SCENARIO("The reflected color for a reflective material") {
  GIVEN("") {
    auto world = rt::World::defaultWorld();
    auto shape = new rt::Plane();
    shape->material().setReflective(0.5);
    shape->transform() = util::Matrixd::translation(0,-1,0);
    world->shapes().emplace_back(shape);
    auto r = rt::Ray(util::Tuple::point(0,0,-3), util::Tuple::vector(0,-sqrt(2)/2,sqrt(2)/2));
    auto i  = rt::Intersection(sqrt(2),world->shapes()[2].get());
    auto comps = rt::prepareComputations(i,r);
    auto c = rt::reflectedColor(*world,comps);
    THEN("") {
      REQUIRE(c == util::Color(0.19033,0.23791,0.14274));
    }
  }
}

SCENARIO("shadeHit with a reflective material") {
  GIVEN("") {
    auto world = rt::World::defaultWorld();
    auto shape = new rt::Plane();
    shape->material().setReflective(0.5);
    shape->transform() = util::Matrixd::translation(0,-1,0);
    world->shapes().emplace_back(shape);
    auto r = rt::Ray(util::Tuple::point(0,0,-3), util::Tuple::vector(0,-sqrt(2)/2,sqrt(2)/2));
    auto i  = rt::Intersection(sqrt(2),world->shapes()[2].get());
    auto comps = rt::prepareComputations(i,r);
    auto c = rt::Shader::shadeHit(*world,comps);
    THEN("") {
      REQUIRE(c == util::Color(0.87676,0.92434,0.82918));
    }
  }
}

SCENARIO("colorAt with mutually reflective surfaces") {
  GIVEN("") {
    auto world = rt::World();
    world.lights().emplace_back(std::make_unique<rt::PointLight>(util::Tuple::point(0,0,0),util::Color(1,1,1)));
    auto lower = new rt::Plane();
    lower->material().setReflective(1);
    lower->transform() = util::Matrixd::translation(0,-1,0);
    world.shapes().emplace_back(lower);
    auto upper = new rt::Plane();
    upper->material().setReflective(1);
    upper->transform() = util::Matrixd::translation(0,1,0);
    world.shapes().emplace_back(upper);
    auto r = rt::Ray(util::Tuple::point(0,0,0), util::Tuple::vector(0,1,0));
    THEN("") {
      REQUIRE_NOTHROW(rt::colorAt(world,r));
    }
  }
}


SCENARIO("The reflected color at the maximum recursive depth") {
  GIVEN("") {
    auto world = rt::World::defaultWorld();
    auto shape = new rt::Plane();
    shape->material().setReflective(0.5);
    shape->transform() = util::Matrixd::translation(0,-1,0);
    world->shapes().emplace_back(shape);
    auto r = rt::Ray(util::Tuple::point(0,0,-3), util::Tuple::vector(0,-sqrt(2)/2,sqrt(2)/2));
    auto i  = rt::Intersection(sqrt(2),world->shapes()[2].get());
    auto comps = rt::prepareComputations(i,r);
    auto c = rt::reflectedColor(*world,comps,0);
    THEN("") {
      REQUIRE(c == util::Color(0,0,0));
    }
  }
}
SCENARIO("The refracted color with an opaque surface") {
  GIVEN("") {
    auto world = rt::World::defaultWorld();
    auto shape = world->shapes()[0].get();
    auto ray = rt::Ray(util::Tuple::point(0,0,-5), util::Tuple::vector(0,0,1));
    auto xs = rt::Intersections{rt::Intersection(4,shape), rt::Intersection(6,shape)};
    WHEN(""){
      auto comps = rt::prepareComputations(xs[0],ray,xs);
      auto c = rt::refractedColor(*world,comps,5);
      THEN(""){
        REQUIRE(c == util::Color(0,0,0));
      }
    }
  }
}
SCENARIO("The refracted color at the maximum recursive dept") {
  GIVEN("") {
    auto world = rt::World::defaultWorld();
    auto shape = world->shapes()[0].get();
    shape->material().setRefractionIndex(1.5);
    shape->material().setTransparency( 1.0);
    auto ray = rt::Ray(util::Tuple::point(0,0,-5), util::Tuple::vector(0,0,1));
    auto xs = rt::Intersections{rt::Intersection(4,shape), rt::Intersection(6,shape)};
    WHEN(""){
      auto comps = rt::prepareComputations(xs[0],ray,xs);
      auto c = rt::refractedColor(*world,comps,0);
      THEN(""){
        REQUIRE(c == util::Color(0,0,0));
      }
    }
  }
}
SCENARIO("The refracted color under total internal reflection") {
  GIVEN("") {
    auto world = rt::World::defaultWorld();
    auto shape = world->shapes()[0].get();
    shape->material().setRefractionIndex(1.5);
    shape->material().setTransparency( 1.0);
    auto ray = rt::Ray(util::Tuple::point(0,0,sqrt(2)/2), util::Tuple::vector(0,1,0));
    auto xs = rt::Intersections{rt::Intersection(-sqrt(2)/2,shape), rt::Intersection(sqrt(2)/2,shape)};
    WHEN(""){
      auto comps = rt::prepareComputations(xs[1],ray,xs);
      auto c = rt::refractedColor(*world,comps,5);
      THEN(""){
        REQUIRE(c == util::Color(0,0,0));
      }
    }
  }
}

SCENARIO("The refracted color with a refracted ray") {
  GIVEN("") {
    auto world = rt::World::defaultWorld();
    auto A = world->shapes()[0].get();
    A->material().setAmbient(1.0);
    A->material().setPattern( std::make_unique<rt::TestPattern>(util::Color::BLACK, util::Color::BLACK));
    auto B = world->shapes()[1].get();
    B->material().setTransparency(1.0);
    B->material().setRefractionIndex( 1.5);
    auto ray = rt::Ray(util::Tuple::point(0,0,0.1), util::Tuple::vector(0,1,0));
    auto xs = rt::Intersections{rt::Intersection(-0.9899,A), rt::Intersection(-0.4899,B),
      rt::Intersection(0.4899,B),rt::Intersection(0.9899,A)};
    WHEN(""){
      auto comps = rt::prepareComputations(xs[2],ray,xs);
      //std::swap(comps.n1,comps.n2);
      auto c = rt::refractedColor(*world,comps,5);
      THEN(""){
        REQUIRE(c == util::Color(0,0.99888,0.04725));
      }
    }
  }
}

SCENARIO("ShadeHit with a transparent material") {
  GIVEN("") {
    auto world = rt::World::defaultWorld();
    world->shapes().emplace_back(std::make_unique<rt::Plane>());
    auto floor = world->shapes()[2].get();
    floor->transform() = util::Matrixd::translation(0,-1,0);
    floor->material().setTransparency(0.5);
    floor->material().setRefractionIndex(1.5);
    world->shapes().emplace_back(std::make_unique<rt::Sphere>());
    auto ball = world->shapes()[3].get();
    ball->transform() = util::Matrixd::translation(0,-3.5,-0.5);
    ball->material().setColor(util::Color(1,0,0));
    ball->material().setAmbient(0.5);

    auto ray = rt::Ray(util::Tuple::point(0,0,-3), util::Tuple::vector(0,-sqrt(2)/2,sqrt(2)/2));
    auto xs = rt::Intersections{rt::Intersection(sqrt(2),world->shapes()[2].get())};
    WHEN(""){
      auto comps = rt::prepareComputations(xs[0],ray,xs);
      auto c = rt::Shader::shadeHit(*world,comps,5);
      THEN(""){
        REQUIRE(c == util::Color(0.93642,0.68642,0.68642));
      }
    }
  }
}

SCENARIO("ShadeHit with a reflective, transparent material") {
  GIVEN("") {
    auto world = rt::World::defaultWorld();
    world->shapes().emplace_back(std::make_unique<rt::Plane>());
    auto floor = world->shapes()[2].get();
    floor->transform() = util::Matrixd::translation(0,-1,0);
    floor->material().setTransparency(0.5);
    floor->material().setReflective(0.5);
    floor->material().setRefractionIndex(1.5);
    world->shapes().emplace_back(std::make_unique<rt::Sphere>());
    auto ball = world->shapes()[3].get();
    ball->transform() = util::Matrixd::translation(0,-3.5,-0.5);
    ball->material().setColor(util::Color(1,0,0));
    ball->material().setAmbient(0.5);
    auto ray = rt::Ray(util::Tuple::point(0,0,-3), util::Tuple::vector(0,-sqrt(2)/2,sqrt(2)/2));
    auto xs = rt::Intersections{rt::Intersection(sqrt(2),world->shapes()[2].get())};
    WHEN(""){
      auto comps = rt::prepareComputations(xs[0],ray,xs);
      auto c = rt::Shader::shadeHit(*world,comps,5);
      THEN(""){
        REQUIRE(c == util::Color(0.93391,0.69643,0.69243));
      }
    }
  }
}

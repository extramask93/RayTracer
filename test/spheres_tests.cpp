//
// Created by damian on 06.07.2020.
//
#include <catch2/catch.hpp>
#include <ray/Ray.h>
#include <shapes/Sphere.h>
#include <intersections/Intersection.h>
#include <materials/Material.h>
#include <intersections/Intersections.h>
SCENARIO("A ray intersects a sphere at two points") {
  GIVEN("a ray") {
    auto ray = rt::Ray(util::Tuple::point(0,0,-5),util::Tuple::vector(0,0,1));
    AND_GIVEN("a sphere") {
      auto sphere = rt::Sphere();
      WHEN("ray intersects sphere") {
        auto xs = sphere.intersect(ray);
        THEN("There are to intersection points") {
          REQUIRE(xs.size() == 2);
          AND_THEN("Those points lay x units away from origin") {
            REQUIRE(xs[0].t() == 4.0);
            REQUIRE(xs[1].t() == 6.0);
          }
        }
      }
    }
  }
}
SCENARIO("A ray intersects sphere at a tangent") {
  GIVEN("A ray") {
    auto ray = rt::Ray(util::Tuple::point(0,1,-5),util::Tuple::vector(0,0,1));
    AND_GIVEN("A sphere") {
      auto s = rt::Sphere();
      WHEN("Intersecting") {
        auto xs = s.intersect(ray);
        THEN("") {
          REQUIRE(xs.size() == 2);
          REQUIRE(xs[0].t() == 5.0);
          REQUIRE(xs[1].t() == 5.0);
        }
      }
    }
  }
}
SCENARIO("A ray misses a sphere") {
  GIVEN("A ray") {
    auto ray = rt::Ray(util::Tuple::point(0,2,-5),util::Tuple::vector(0,0,1));
    AND_GIVEN("A sphere") {
      auto s = rt::Sphere();
      WHEN("Intersecting") {
        auto xs = s.intersect(ray);
        THEN("") {
          REQUIRE(xs.size() == 0);
        }
      }
    }
  }
}
SCENARIO("A ray originates from inside a sphere") {
  GIVEN("A ray") {
    auto ray = rt::Ray(util::Tuple::point(0,0,0),util::Tuple::vector(0,0,1));
    AND_GIVEN("A sphere") {
      auto s = rt::Sphere();
      WHEN("Intersecting") {
        auto xs = s.intersect(ray);
        THEN("") {
          REQUIRE(xs.size() == 2);
          REQUIRE(xs[0].t() == -1.0);
          REQUIRE(xs[1].t() == 1.0);
        }
      }
    }
  }
}
SCENARIO("A sphere is behind the ray") {
  GIVEN("A ray") {
    auto ray = rt::Ray(util::Tuple::point(0,0,5),util::Tuple::vector(0,0,1));
    AND_GIVEN("A sphere") {
      auto s = rt::Sphere();
      WHEN("Intersecting") {
        auto xs = s.intersect(ray);
        THEN("") {
          REQUIRE(xs.size() == 2);
          REQUIRE(xs[0].t() == -6.0);
          REQUIRE(xs[1].t() == -4.0);
        }
      }
    }
  }
}
SCENARIO("Intersect sets the object on the intersection") {
  GIVEN("A ray") {
    auto ray = rt::Ray(util::Tuple::point(0,0,-5), util::Tuple::vector(0,0,1));
    AND_GIVEN("Sphere") {
      auto sphere =  rt::Sphere();
      WHEN("Intersecting") {
        auto xs = sphere.intersect(ray);
        THEN("") {
          REQUIRE(xs.size() ==2);
          REQUIRE(xs[0].object() == &sphere);
          REQUIRE(xs[1].object() == &sphere);
        }
      }
    }
  }
}
SCENARIO("A sphere's default transformation") {
  GIVEN("A sphere") {
    auto s = rt::Sphere();
    THEN("") {
      REQUIRE(s.transform() == util::Matrixd::Identity(4));
    }
  }
}
SCENARIO("Changing a sphere's transformation") {
  GIVEN("A sphere") {
    auto s = rt::Sphere();
    auto t = util::Matrixd ::translation(2,3,4);
    WHEN("Set transform") {
      s.setTransform(t);
      THEN(""){
        REQUIRE(s.transform() == t);
      }
    }
  }
}
SCENARIO("Intersecting a scaled sphere with a ray") {
  GIVEN("A ray and a sphere") {
    auto r = rt::Ray(util::Tuple::point(0,0,-5),util::Tuple::vector(0,0,1));
    auto s = rt::Sphere();
    WHEN("setting transform and intersecting") {
      s.setTransform(util::Matrixd::scaling(2,2,2));
      auto xs = s.intersect(r);
      THEN("") {
        REQUIRE(xs.size() == 2);
        REQUIRE(xs[0].t() == 3);
        REQUIRE(xs[1].t() == 7);
      }
    }
  }
}

SCENARIO("Intersecting a translated sphere with a ray") {
  GIVEN("A ray and a sphere") {
    auto r = rt::Ray(util::Tuple::point(0,0,-5),util::Tuple::vector(0,0,1));
    auto s = rt::Sphere();
    WHEN("setting transform and intersecting") {
      s.setTransform(util::Matrixd::translation(5,0,0));
      auto xs = s.intersect(r);
      THEN("") {
        REQUIRE(xs.size() == 0);
      }
    }
  }
}

SCENARIO("The normal on a sphere at a point on the x axis") {
  GIVEN("A sphere") {
    auto s = rt::Sphere();
    WHEN("Computing a normal vector") {
      auto n = s.normalAt(util::Tuple::point(1, 0, 0), rt::Intersection(0, nullptr));
      THEN("") {
        REQUIRE(n == util::Tuple::vector(1,0,0));
      }
    }
  }
}
SCENARIO("The normal on a sphere at a point on the y axis") {
  GIVEN("A sphere") {
    auto s = rt::Sphere();
    WHEN("Computing a normal vector") {
      auto n = s.normalAt(util::Tuple::point(0, 1, 0), rt::Intersection(0, nullptr));
      THEN("") {
        REQUIRE(n == util::Tuple::vector(0,1,0));
      }
    }
  }
}
SCENARIO("The normal on a sphere at a point on the z axis") {
  GIVEN("A sphere") {
    auto s = rt::Sphere();
    WHEN("Computing a normal vector") {
      auto n = s.normalAt(util::Tuple::point(0, 0, 1), rt::Intersection(0, nullptr));
      THEN("") {
        REQUIRE(n == util::Tuple::vector(0,0,1));
      }
    }
  }
}
SCENARIO("The normal on a sphere at a nonaxial point") {
  GIVEN("A sphere") {
    auto s = rt::Sphere();
    WHEN("Computing a normal vector") {
      double cord = std::sqrt(3)/3;
      auto n = s.normalAt(util::Tuple::point(cord, cord, cord), rt::Intersection(0, nullptr));
      THEN("") {
        REQUIRE(n == util::Tuple::vector(cord,cord,cord));
      }
    }
  }
}
SCENARIO("The normal is a normalized vector") {
  GIVEN("A sphere") {
    auto s = rt::Sphere();
    WHEN("Computing a normal vector") {
      double cord = std::sqrt(3)/3;
      auto n = s.normalAt(util::Tuple::point(cord, cord, cord), rt::Intersection(0, nullptr));
      auto k = n;
      n.normalize();
      THEN("") {
        REQUIRE(k == n);
      }
    }
  }
}
SCENARIO("Computing the normal on a translated sphere") {
  GIVEN("A sphere and transfrom") {
    auto s = rt::Sphere();
    s.setTransform(util::Matrixd::translation(0,1,0));
    WHEN("Computing normal") {
      auto normal = s.normalAt(util::Tuple::point(0, 1.70711, -0.70711), rt::Intersection(0, nullptr));
      THEN("") {
        REQUIRE(normal == util::Tuple::vector(0,0.70711,-0.70711));
      }
    }
  }
}
SCENARIO("Computing the normal on a transformed sphere") {
  GIVEN("A sphere and transfrom") {
    auto s = rt::Sphere();
    s.setTransform(util::Matrixd::scaling(1,0.5,1).rotate_z(std::numbers::pi/5));
    WHEN("Computing normal") {
      auto normal = s.normalAt(util::Tuple::point(0, sqrt(2) / 2, -sqrt(2) / 2), rt::Intersection(0, nullptr));
      THEN("") {
        REQUIRE(normal == util::Tuple::vector(0,0.97014,-0.24254));
      }
    }
  }
}
SCENARIO("A sphere has a default material") {
  GIVEN("A sphere") {
    auto s = rt::Sphere();
    WHEN("Obstaining material") {
      auto m = s.material();
      THEN(""){
        REQUIRE(m == rt::Material());
      }
    }
  }
}
SCENARIO("A sphere may be assigned a material") {
  GIVEN("A sphere") {
    auto s = rt::Sphere();
    auto m = s.material();
    m.setAmbient(1);
    WHEN("Obstaining material") {
      s.setMaterial(m);
      THEN(""){
        REQUIRE(m == s.material());
      }
    }
  }
}
SCENARIO("A helper function for producing a sphere with a glassy material") {
  GIVEN("A sphere") {
    auto s = rt::Sphere::glassSphere();
    WHEN("") {
      THEN(""){
        REQUIRE(s.material().transparency() == 1.0);
        REQUIRE(s.material().refractionIndex() == 1.5);
      }
    }
  }
}

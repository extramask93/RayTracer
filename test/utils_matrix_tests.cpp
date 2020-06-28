//
// Created by damian on 19.06.2020.
//

#include <catch2/catch.hpp>
#include <Color.h>
#include <Canvas.h>
#include <CanvasPrinter.h>
#include <fstream>
#include <algorithm>
#include <eigen3/Eigen/Eigen>
#include <string>
#include <sstream>
#include <Matrix.h>
SCENARIO("Constructing and inspecting 4x4 matrix")
{
  GIVEN("Matrix 4x4")
  {
    util::Matrix<double> m(4,4);
    m << 1,2,3,4,
        5.5,6.5,7.5,8.5,
      9,10,11,12,
      13.5,14.5,15.5,16.5;
    THEN("Elements are filled")
    {
      REQUIRE(m(0,0) == 1);
      REQUIRE(m(0,3) == 4);
      REQUIRE(m(1,0) == 5.5);
      REQUIRE(m(1,2) == 7.5);
      REQUIRE(m(2,2) == 11);
      REQUIRE(m(3,0) == 13.5);
      REQUIRE(m(3,2) == 15.5);

    }
  }
}
SCENARIO("Constructing and inspecting 2x2 matrix")
{
  GIVEN("Matrix 2x2")
  {
    util::Matrix<double> m(2,2);
    m << -3,5,1,-2;
    THEN("Elements are filled")
    {
      REQUIRE(m(0,0) == -3);
      REQUIRE(m(0,1) == 5);
      REQUIRE(m(1,0) == 1);
      REQUIRE(m(1,1) == -2);
    }
  }
}
SCENARIO("Matrix equality with identical matrices") {
  GIVEN("Matrix A") {
    util::Matrix<double> A(4,4);
    A<<1,2,3,4,
      5,6,7,8,
      9,8,7,6,
      5,4,3,2;
    AND_GIVEN("Matrix B") {
      util::Matrix<double> B(4,4);
      B<<1,2,3,4,
        5,6,7,8,
        9,8,7,6,
        5,4,3,2;
      THEN("A==B") {
        REQUIRE(A == B);
      }
    }
  }
}
SCENARIO("Matrix equality with different matrices") {
  GIVEN("Matrix A") {
    util::Matrix<double> A(4,4);
    A<<1,2,3,4,
      5,6,7,8,
      9,8,7,6,
      5,4,3,2;
    AND_GIVEN("Matrix B") {
      util::Matrix<double> B(4,4);
      B<<2,3,4,5,
        6,7,8,9,
        8,7,6,5,
        4,3,2,1;
      THEN("A==B") {
        REQUIRE(A != B);
      }
    }
  }
}
SCENARIO("Multiplying two matrices") {
  GIVEN("Matrix A") {
    util::Matrix<double> A(4,4);
    A<<1,2,3,4,
      5,6,7,8,
      9,8,7,6,
      5,4,3,2;
    AND_GIVEN("Matrix B") {
      util::Matrix<double> B(4,4);
      B<<-2,1,2,3,
        3,2,1,-1,
        4,3,6,5,
        1,2,7,8;
      AND_GIVEN("Matrix C")
      {
        util::Matrix<double> C(4,4);
        C << 20,22,50,48,
          44,54,114,108,
          40,58,110,102,
          16,26,46,42;
        THEN("A*B == C")
        {
          REQUIRE(A * B == C);
        }
      }
    }
  }
}
SCENARIO("Matrix multiplied by tuple") {
  GIVEN("Matrix A") {
    util::Matrix<double> A(4,4);
    A<<1,2,3,4,
      2,4,4,2,
      8,6,4,1,
      0,0,0,1;
    AND_GIVEN("Tuple B") {
      util::Tuple B(1,2,3,1);
        THEN("A*B == C")
        {
          REQUIRE(A * B == util::Tuple(18,24,33,1));
        }
    }
  }
}
SCENARIO("Multiplying matrix by identity matrix") {
  GIVEN("Matrix A") {
    util::Matrix<double> A(4,4);
    A<<0,1,2,4,
      1,2,4,8,
      2,4,8,16,
      4,8,16,32;
    AND_GIVEN("Identity matrix B") {
      auto B = util::Matrix<double>::Identity(4);
      THEN("A*B == A")
      {
        REQUIRE(A * B == A);
      }
    }
  }
}

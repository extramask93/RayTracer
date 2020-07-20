//
// Created by damian on 19.06.2020.
//

#include <catch2/catch.hpp>
#include <Color.h>
#include <Canvas.h>
#include <CanvasPrinter.h>
#include <fstream>
#include <algorithm>
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
SCENARIO("Transposing a matrix") {
  GIVEN("Matrix A") {
    util::Matrix<double> A(4,4);
    A<<0,9,3,0,
      9,8,0,8,
      1,8,5,3,
      0,0,5,8;
    AND_GIVEN("Transpose of matrix A") {
      util::Matrix<double> T(4,4);
      T<<0,9,1,0,
        9,8,8,0,
        3,0,5,5,
        0,8,3,8;
      THEN("A.transpose == T")
      {
        REQUIRE(A.transpose() == T);
      }
    }
  }
}
SCENARIO("Transposing an identity matrix") {
  GIVEN("Identity Matrix A") {
    util::Matrix<double> A = util::Matrix<double>::Identity(4);
      THEN("A.transpose == A")
      {
        REQUIRE(A.transpose() == A);
      }
  }
}
SCENARIO("Calculating determinant of a 2x2 matrix") {
  GIVEN("Matrix A") {
    util::Matrix<double> A(2,2);
    A<< 1,5,-3,2;
    THEN("A.det() == 17")
    {
      REQUIRE(A.det() == 17);
    }
  }
}
SCENARIO("A submatrix of a 3x3 matrix is a 2x2 matrix") {
  GIVEN("Matrix 3x3 A") {
    util::Matrix<double> A(3,3);
    A<< 1,5,0,
      -3,2,7,
      0,6,-3;
    THEN("A.submatrix(0,2) is the following matrix")
    {
      util::Matrix<double> submatrix(2,2);
      submatrix<<-3,2,0,6;
      REQUIRE(A.submatrix(0,2) == submatrix);
    }
  }
}
SCENARIO("A submatrix of a 4x4 matrix is a 3x3 matrix") {
  GIVEN("Matrix 3x3 A") {
    util::Matrix<double> A(4,4);
    A<< -6,1,1,6,
      -8,5,8,6,
      -1,0,8,2,
      -7,1,-1,1;
    THEN("A.submatrix(2,1) is the following matrix")
    {
      util::Matrix<double> submatrix(3,3);
      submatrix<<-6,1,6,-8,8,6,-7,-1,1;
      REQUIRE(A.submatrix(2,1) == submatrix);
    }
  }
}
SCENARIO("Calculating minor a 3x3 matrix") {
  GIVEN("Matrix 3x3 A") {
    util::Matrix<double> A(3,3);
    A<< 3,5,0,2,-1,-7,6,-1,5;
    AND_GIVEN("B = A.submatrinx(1,0)")
    {
      auto B = A.submatrix(1,0);
      THEN("Determinant(B) ==25 ")
      {
        REQUIRE(B.det() == 25);
        REQUIRE(A.mminor(1,0) == 25);
      }
    }
  }
}

SCENARIO("Calculating cofactor a 3x3 matrix") {
  GIVEN("Matrix 3x3 A") {
    util::Matrix<double> A(3,3);
    A<< 3,5,0,
      2,-1,-7,
      6,-1,5;
      THEN("A.minor(0,0) == -12 ")
      {
        REQUIRE(A.mminor(0, 0) == -12);
        REQUIRE(A.cofactor(0,0) == -12);
        REQUIRE(A.mminor(1,0) == 25);
        REQUIRE(A.cofactor(1,0) == -25);
      }
  }
}
SCENARIO("Calculating determinant of a 3x3 matrix") {
  GIVEN("Matrix 3x3 A") {
    util::Matrix<double> A(3,3);
    A<< 1,2,6,
      -5,8,-4,
      2,6,4;
    THEN("A.cofactor(0,0) == 56 ")
    {
      REQUIRE(A.cofactor(0, 0) == 56);
      REQUIRE(A.cofactor(0,1) == 12);
      REQUIRE(A.cofactor(0,2) == -46);
      REQUIRE(A.det() == -196);
    }
  }
}
SCENARIO("Calculating determinant of a 4x4 matrix") {
  GIVEN("Matrix 4x4 A") {
    util::Matrix<double> A(4,4);
    A<< -2,-8,3,5,
      -3,1,7,3,
      1,2,-9,6,
      -6,7,7,-9;
    THEN("A.cofactor(0,0) == 690 ")
    {
      REQUIRE(A.cofactor(0, 0) == 690);
      REQUIRE(A.cofactor(0,1) == 447);
      REQUIRE(A.cofactor(0,2) == 210);
      REQUIRE(A.cofactor(0,3) == 51);
      REQUIRE(A.det() == -4071);
    }
  }
}
SCENARIO("Testing an invertible matrix for inveribility") {
  GIVEN("Matrix 4x4 A") {
    util::Matrix<double> A(4,4);
    A<< 6,4,4,4,
      5,5,7,6,
      4,-9,3,-7,
      9,1,7,-6;
    THEN("A.det() ==-2120 ")
    {
      REQUIRE(A.det() == -2120);
      REQUIRE(A.isInvertible() == true);
    }
  }
}

SCENARIO("Testing a noninvertible matrix for inveribility") {
  GIVEN("Matrix 4x4 A") {
    util::Matrix<double> A(4,4);
    A<< -4,2,-2,-3,
      9,6,2,6,
      0,-5,1,-5,
      0,0,0,0;
    THEN("A.det() ==0 ")
    {
      REQUIRE(A.det() < 0.00001);
      REQUIRE(A.isInvertible() == false);
    }
  }
}
SCENARIO("Calculating the inverse of a matrix") {
  GIVEN("Matrix 4x4 A") {
    util::Matrix<double> A(4,4);
    A<< -5,2,6,-8,
      1,-5,1,8,
      7,7,-6,-7,
      1,-3,7,4;
    AND_GIVEN("Matrix B which is it's inverse")
    {
      auto B = A.inverse();
      //util::Matrix<double> B2(4,4);

      THEN("A.det() == 532 ")
      {
        REQUIRE(A.det() == 532);
        REQUIRE(A.cofactor(2,3)== -160);
        REQUIRE(B(3,2) == -160/532.0);
        REQUIRE(A.cofactor(3,2) == 105);
        REQUIRE(B(2,3) == (105.0/532.0));
      }
    }
  }
}
SCENARIO("Multiplying matrix by its inverse") {
  GIVEN("Matrix A") {
    util::Matrix<double> A(4,4);
    A<< 3,-9,7,3,
      3,-8,2,-9,
      -4,4,4,1,
      -6,5,-1,1;
    AND_GIVEN("Matrix B - its inverse") {
      util::Matrix<double> B(4,4);
      B<< 8,2,2,2,
          3,-1,7,0,
          7,0,5,4,
          6,-2,0,5;
      AND_GIVEN("MAtirx C = A*B") {
        auto C = A*B;
        auto i = B.inverse();
        (void)i;
        auto D = C*B.inverse();
        THEN("C*B.inverse() == A") {
          REQUIRE(D == A);
        }
      }
    }
  }
}
SCENARIO("Inverse of 2x2 matrix") {
  util::Matrix<double> m(2,2);
  m << 5,2,-7,-3;
  auto inv = m.inverse();
  auto c = m * inv;
  REQUIRE(m.Identity(2) == c);
}

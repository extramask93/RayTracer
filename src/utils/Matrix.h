//
// Created by damian on 19.06.2020.
//

#ifndef MYPROJECT_MATRIX_H
#define MYPROJECT_MATRIX_H
#include <vector>
#include <Tuple.h>
#include <cmath>
#pragma push_macro("minor")
#undef minor
#ifndef M_PI
  #define M_PI 3.14159265358979323846
#endif
namespace util {

template<typename T>
class Matrix
{
public:
  Matrix(unsigned rows, unsigned columns);
  [[nodiscard]] constexpr T operator()(unsigned row, unsigned column) const;
  [[nodiscard]] constexpr T& operator()(unsigned row, unsigned column);
  [[nodiscard]] constexpr bool operator==(const Matrix<T> &other) const;
  [[nodiscard]] constexpr bool operator!=(const Matrix<T> &other) const;
  [[nodiscard]] constexpr Matrix<T> operator*(const Matrix<T> &other) const;
  [[nodiscard]] constexpr unsigned nrOfCells() const;
  [[nodiscard]] constexpr bool isInvertible() const;
  [[nodiscard]] constexpr unsigned nrOfRows() const;
  [[nodiscard]] constexpr unsigned nrOfColumns() const;
  [[nodiscard]] constexpr Matrix<T> transpose() const;
  [[nodiscard]] constexpr Matrix<T> inverse() const;
  [[nodiscard]] constexpr T det() const;
  [[nodiscard]] constexpr Matrix<T> submatrix(unsigned row, unsigned column) const;
  [[nodiscard]] constexpr T mminor(unsigned row, unsigned column) const;
  [[nodiscard]] constexpr T cofactor(unsigned row, unsigned column) const;
  [[nodiscard]] constexpr Matrix<T>& translate(T x, T y, T z);
  [[nodiscard]] constexpr Matrix<T>& scale(T x, T y, T z);
  [[nodiscard]] constexpr Matrix<T>& rotate_x(double rad);
  [[nodiscard]] constexpr Matrix<T>& rotate_y(double rad);
  [[nodiscard]] constexpr Matrix<T>& rotate_z(double rad);
  [[nodiscard]] constexpr Matrix<T>& shear(double Xy, double Xz, double Yx, double Yz, double Zx, double Zy);
  //
  [[nodiscard]] static Matrix<T> Identity(unsigned size);
  [[nodiscard]] static Matrix<T> translation(T x, T y, T z);
  [[nodiscard]] static Matrix<T> scaling(T x, T y, T z);
  [[nodiscard]] static Matrix<T> rotation_x(double rad);
  [[nodiscard]] static Matrix<T> rotation_y(double rad);
  [[nodiscard]] static Matrix<T> rotation_z(double rad);
  [[nodiscard]] static Matrix<T> shearing(double Xy, double Xz, double Yx, double Yz, double Zx, double Zy);
  struct Loader {
    Matrix<T> &m_m;
    unsigned m_i;
    Loader(Matrix<T> &m, unsigned i) : m_m(m), m_i(i) {}
    Loader operator , (T d) {
      m_m(m_i/m_m.m_rows, m_i%m_m.m_rows) = d;
      return Loader(m_m,m_i+1);
    };
  };
  Loader operator<<(T data);
private:
  static bool equal(double lhs, double rhs)
  {
    auto difference = std::abs(lhs - rhs);
    return difference <= eps_;
  }
private:
  unsigned m_columns;
  unsigned m_rows;
  std::vector<T> m_data;
  static constexpr double eps_ = 0.00001;
};
template<typename T>
constexpr util::Tuple operator*(const Matrix<T> &m, const util::Tuple &t) {

  Tuple result(t);
  for(unsigned r = 0 ;r < m.nrOfRows(); r++) {
    for(unsigned  c = 0; c < 4.;c++) {
      double sum = 0.0;
      for(unsigned i=0; i<m.nrOfRows();i++) {
        sum += m(r,i) * t(i,c);
      }
      result(r,c) =sum;
    }
  }
  return result;
}

template<typename T>
Matrix<T>::Matrix(unsigned int rows, unsigned int columns) : m_columns(columns), m_rows(rows)
{
  m_data.resize(m_columns*m_rows,0.0);
}
template<typename T>
constexpr T Matrix<T>::operator()(unsigned int row, unsigned int column) const
{
  return m_data.at(row * m_columns + column);
}
template<typename T>
typename Matrix<T>::Loader Matrix<T>::operator<<(T data)
{
  this->operator()(0,0) = data;
  return Loader(*this,1);
}
template<typename T>
constexpr T &Matrix<T>::operator()(unsigned row, unsigned column)
{
  return m_data.at(row * m_columns + column);
}
template<typename T>
constexpr bool Matrix<T>::operator==(const Matrix<T> &other) const
{
  if(nrOfCells() != other.nrOfCells()) {
    return false;
  }
  for(unsigned i =0; i < nrOfCells(); i++) {
    if(!equal(m_data[i], other.m_data[i])) {
      return false;
    }
  }
  return true;
}
template<typename T>
constexpr unsigned Matrix<T>::nrOfCells() const
{
  return m_columns*m_rows;
}
template<typename T>
constexpr bool Matrix<T>::operator!=(const Matrix<T> &other) const
{
  return !(*this == other);
}
template<typename T>
constexpr Matrix<T> Matrix<T>::operator*(const util::Matrix<T> &m) const
{
  Matrix result(*this);
  for(unsigned r = 0 ;r < m_rows; r++) {
    for(unsigned  c = 0; c < m.m_columns;c++) {
      double sum = 0.0;
      for(unsigned i=0; i<m_rows;i++) {
        sum += operator()(r,i) * m(i,c);
      }
      result(r,c) =sum;
    }
  }
  return result;

}
template<typename T>
constexpr unsigned Matrix<T>::nrOfColumns() const
{
  return m_columns;
}
template<typename T>
constexpr unsigned Matrix<T>::nrOfRows() const
{
  return m_rows;
}
template<typename T>
Matrix<T> Matrix<T>::Identity(unsigned size)
{
  Matrix<T> m(size, size);
  for(unsigned row = 0; row < m.nrOfRows(); row++) {
        m(row,row) = 1;
  }
  return m;
}
template<typename T>
constexpr Matrix<T> Matrix<T>::transpose() const
{
  util::Matrix<T> result(nrOfColumns(),nrOfRows());
  for(unsigned row = 0; row < nrOfRows(); row++) {
    for(unsigned col = 0; col < nrOfColumns();col++) {
       result(col,row) = operator()(row,col);
    }
  }
  return result;
}
template<typename T>
constexpr T Matrix<T>::det() const
{
  T result{};
  if(nrOfRows() == 2 && nrOfColumns() ==2) {
    result = operator()(0, 0) * operator()(1, 1) - operator()(0, 1) * operator()(1, 0);
  }
  else {
    for(unsigned i = 0; i < nrOfColumns(); i++) {
      result += operator()(0,i) * cofactor(0,i);
    }
  }
  return result;
}
template<typename T>
constexpr Matrix<T> Matrix<T>::submatrix(unsigned row, unsigned column) const
{
  Matrix<T> result(nrOfRows()-1,nrOfColumns()-1);
  unsigned rowcnt = 0;
  unsigned colcnt = 0;

  for(unsigned r = 0; r < nrOfRows(); r++) {
    colcnt = 0;
    if(r ==row) {
      continue;
    }
    for(unsigned c =0; c < nrOfColumns(); c++) {
      if(column == c) {
        continue;
      }
      result(rowcnt,colcnt) = operator()(r,c);
      colcnt++;
    }
    rowcnt++;
  }
  return result;
}
template<typename T>
constexpr T Matrix<T>::mminor(unsigned int row, unsigned int column) const
{

  return submatrix(row,column).det();
}
template<typename T>
constexpr T Matrix<T>::cofactor(unsigned int row, unsigned int column) const
{
  auto m = mminor(row,column);
  if ((row + column) % 2) {
    return -m;
  } else {
    return m;
  }
}
template<typename T>
constexpr bool Matrix<T>::isInvertible() const
{
  return !equal(det(), 0.0);
}
template<typename T>
constexpr Matrix<T> Matrix<T>::inverse() const
{
  if(!isInvertible()) {
    throw std::runtime_error("Matrix not invertible");
  }
  auto M = *this;
  auto d = det();
  if(nrOfRows() ==2 ) {
    M(0,0) = operator()(1,1)/d;
    M(0,1) = -operator()(0,1)/d;
    M(1,0) = -operator()(1,0)/d;
    M(1,1) = operator()(0,0)/d;
    return M;
  }
  for(unsigned row = 0 ; row < nrOfRows(); row++) {
    for(unsigned col = 0; col < nrOfColumns(); col++) {
      auto c = cofactor(row,col);
      M(col,row) = c / d;
    }
  }
  return M;
}
template<typename T>
Matrix<T> Matrix<T>::translation(T x, T y, T z)
{
  auto result = util::Matrix<T>::Identity(4);
  result(0,3) = x;
  result(1,3) = y;
  result(2,3) = z;
  return result;
}
template<typename T>
Matrix<T> Matrix<T>::scaling(T x, T y, T z)
{
  auto result = util::Matrix<T>::Identity(4);
  result(0,0)=x;
  result(1,1) = y;
  result(2,2)=z;
  return result;
}
template<typename T>
Matrix<T> Matrix<T>::rotation_x(double rad)
{
  auto result = util::Matrix<T>::Identity(4);
  result(1,1) = cos(rad);
  result(2,2) = cos(rad);
  result(2,1) =  sin(rad);
  result(1,2) = -sin(rad);
  return result;
}
template<typename T>
Matrix<T> Matrix<T>::rotation_y(double rad)
{
  auto result = util::Matrix<T>::Identity(4);
  result(0,0) = cos(rad);
  result(2,0) = -sin(rad);
  result(2,2) = cos(rad);
  result(0,2) = sin(rad);
  return result;
}
template<typename T>
Matrix<T> Matrix<T>::rotation_z(double rad)
{
  auto result = util::Matrix<T>::Identity(4);
  result(0,0) = cos(rad);
  result(0,1) = -sin(rad);
  result(1,1) = cos(rad);
  result(1,0) = sin(rad);
  return result;
}
template<typename T>
Matrix<T> Matrix<T>::shearing(double Xy, double Xz, double Yx, double Yz, double Zx, double Zy)
{
  auto result = util::Matrix<T>::Identity(4);
  result(0,1) = Xy;
  result(0,2)= Xz;
  result(1,0) = Yx;
  result(1,2)= Yz;
  result(2,0)=Zx;
  result(2,1)=Zy;
  return result;
}
template<typename T>
constexpr Matrix<T> &Matrix<T>::translate(T x, T y, T z)
{
  *this = *this * translation(x,y,z);
  return *this;
}
template<typename T>
constexpr Matrix<T> &Matrix<T>::scale(T x, T y, T z)
{
  *this = *this * scaling(x,y,z);
  return *this;
}
template<typename T>
constexpr Matrix<T> &Matrix<T>::rotate_x(double rad)
{
  *this = *this * rotation_x(rad);
  return *this;
}
template<typename T>
constexpr Matrix<T> &Matrix<T>::rotate_y(double rad)
{
  *this = *this * rotation_y(rad);
  return *this;
}
template<typename T>
constexpr Matrix<T> &Matrix<T>::rotate_z(double rad)
{
  *this = *this * rotation_z(rad);
  return *this;
}
template<typename T>
constexpr Matrix<T> &Matrix<T>::shear(double Xy, double Xz, double Yx, double Yz, double Zx, double Zy)
{
  *this = *this * shear(Xy,Xz,Yx,Yz,Zx,Zy);
  return *this;
}

using Matrixd = Matrix<double>;
}// namespace util
#pragma pop_macro("minor")
#endif//MYPROJECT_MATRIX_H

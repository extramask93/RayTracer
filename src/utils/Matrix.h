//
// Created by damian on 19.06.2020.
//

#ifndef MYPROJECT_MATRIX_H
#define MYPROJECT_MATRIX_H
#include <vector>
#include <Tuple.h>
#pragma push_macro("minor")
#undef minor
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
  [[nodiscard]] constexpr unsigned nrOfRows() const;
  [[nodiscard]] constexpr unsigned nrOfColumns() const;
  [[nodiscard]] constexpr Matrix<T> transpose() const;
  [[nodiscard]] constexpr T det() const;
  [[nodiscard]] constexpr Matrix<T> submatrix(unsigned row, unsigned column) const;
  [[nodiscard]] constexpr T mminor(unsigned row, unsigned column) const;
  [[nodiscard]] constexpr T cofactor(unsigned row, unsigned column) const;
  static Matrix<T> Identity(unsigned size);
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
  unsigned m_columns;
  unsigned m_rows;
  std::vector<T> m_data;
};
template<typename T>
util::Tuple operator*(const Matrix<T> &m, const util::Tuple &t) {

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
    if(m_data[i] != other.m_data[i]) {
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
  T result;
  result = operator()(0,0)*operator()(1,1) - operator()(0,1)*operator()(1,0);
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
  return row+column % 2 ? -m : m;
}

}// namespace util
#pragma pop_macro("minor")
#endif//MYPROJECT_MATRIX_H
//
// Created by damian on 11.07.2020.
//

#ifndef MYPROJECT_CAMERA_H
#define MYPROJECT_CAMERA_H

#include <Matrix.h>
namespace rt {

class Camera
{
public:
  Camera(unsigned hsize, unsigned vsize, double fieldOfView);
  [[nodiscard]] constexpr unsigned vsize() const;
  [[nodiscard]] constexpr unsigned hsize() const;
  [[nodiscard]] constexpr double halfWidth() const;
  [[nodiscard]] constexpr double halfHeight() const;
  [[nodiscard]] constexpr double pixelSize() const;
  [[nodiscard]] constexpr double fieldOfView() const;
  [[nodiscard]] constexpr util::Matrixd transform() const;
  void setTransform(const util::Matrixd &transform);
private:
  void calcPixelSize() ;
private:
  unsigned m_hsize;
  unsigned m_vsize;
  double m_fieldOfView;
  util::Matrixd m_transformation;
  double m_pixelSize = 0.0;
  double m_halfWidth = 0.0;
  double m_halfHeight = 0.0;
};
constexpr unsigned rt::Camera::vsize() const
{
  return m_vsize;
}
constexpr unsigned Camera::hsize() const
{
  return m_hsize;
}
constexpr double Camera::fieldOfView() const
{
  return m_fieldOfView;
}
constexpr util::Matrixd Camera::transform() const
{
  return m_transformation;
}

constexpr double Camera::pixelSize() const
{
  return m_pixelSize;
}
constexpr double Camera::halfWidth() const
{
  return m_halfWidth;
}
constexpr double Camera::halfHeight() const
{
  return m_halfHeight;
}

}// namespace rt


#endif//MYPROJECT_CAMERA_H

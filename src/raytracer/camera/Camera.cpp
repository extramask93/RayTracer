//
// Created by damian on 11.07.2020.
//

#include "Camera.h"
using namespace rt;

Camera::Camera(unsigned int hsize, unsigned int vsize, double fieldOfView) : m_hsize(hsize),
                                                                             m_vsize(vsize),
                                                                             m_fieldOfView(fieldOfView),
                                                                             m_transformation(util::Matrixd::Identity(4))
{
  calcPixelSize();
}
void Camera::calcPixelSize()
{
  double aspectRatio = 1.0 * m_hsize/m_vsize;
  double halfView = tan(fieldOfView()/2);
  if(aspectRatio >= 1) {
    m_halfWidth = halfView;
    m_halfHeight = halfView / aspectRatio;
  } else {
    m_halfHeight = halfView;
    m_halfWidth = aspectRatio*halfView;
  }
  m_pixelSize = (m_halfWidth*2) / m_hsize;
}
void Camera::setTransform(const util::Matrixd &transform)
{
  m_transformation = transform;
  calcPixelSize();
}

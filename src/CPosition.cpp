//
// Created by sg on 10.03.18.
//

#include "CPosition.hpp"
CPosition::CPosition(Position_t m_x_axis, Position_t m_y_axis) : m_x_axis(m_x_axis), m_y_axis(m_y_axis) {}
Position_t CPosition::getM_x_axis() const {
  return m_x_axis;
}
Position_t CPosition::getM_y_axis() const {
  return m_y_axis;
}
bool CPosition::operator<(const CPosition &rhs) const {
  if (m_x_axis < rhs.m_x_axis)
    return true;
  if (rhs.m_x_axis < m_x_axis)
    return false;
  return m_y_axis < rhs.m_y_axis;
}
bool CPosition::operator>(const CPosition &rhs) const {
  return rhs < *this;
}
bool CPosition::operator<=(const CPosition &rhs) const {
  return !(rhs < *this);
}
bool CPosition::operator>=(const CPosition &rhs) const {
  return !(*this < rhs);
}
bool CPosition::operator==(const CPosition &rhs) const {
  return m_x_axis==rhs.m_x_axis &&
      m_y_axis==rhs.m_y_axis;
}
bool CPosition::operator!=(const CPosition &rhs) const {
  return !(rhs==*this);
}

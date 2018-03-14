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

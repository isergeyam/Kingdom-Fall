//
// Created by sg on 18.04.18.
//

#include "CMap.hpp"
CMapCell & CMap::operator[](const CPosition &m_pos) {
  return m_map[m_pos.getM_x_axis()][m_pos.getM_y_axis()];
}

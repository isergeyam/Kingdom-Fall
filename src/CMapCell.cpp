//
// Created by sg on 18.04.18.
//

#include "CMapCell.hpp"
CMapCell::CMapCell(CTerrain m_terrain) : m_terrain(std::move(m_terrain)) {
  m_objects.reserve(3);
}

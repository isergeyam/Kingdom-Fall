//
// Created by sg on 18.04.18.
//

#include "CMapCell.hpp"
#include "CGlobalGame.hpp"
CMapCell::CMapCell(const std::shared_ptr<CUnit> &m_unit,
                   const std::shared_ptr<CVillage> &m_village,
                   const std::shared_ptr<CTerrain> &m_terrain)
    : m_unit(m_unit), m_village(m_village), m_terrain(m_terrain) {}
const std::shared_ptr<CUnit> &CMapCell::getM_unit() const {
  return m_unit;
}
const std::shared_ptr<CVillage> &CMapCell::getM_village() const {
  return m_village;
}
const std::shared_ptr<CTerrain> &CMapCell::getM_terrain() const {
  return m_terrain;
}
void CMapCell::setM_unit(const std::shared_ptr<CUnit> &m_unit) {
  ++CGlobalGame::CurGlobalState;
  CMapCell::m_unit = m_unit;
}
void CMapCell::setM_village(const std::shared_ptr<CVillage> &m_village) {
  CMapCell::m_village = m_village;
}
void CMapCell::setM_terrain(const std::shared_ptr<CTerrain> &m_terrain) {
  ++CGlobalGame::CurGlobalState;
  CMapCell::m_terrain = m_terrain;
}
CMapCell::CMapCell(const std::shared_ptr<CTerrain> &m_terrain) : m_terrain(m_terrain) {

}

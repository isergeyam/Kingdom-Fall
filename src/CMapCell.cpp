//
// Created by sg on 18.04.18.
//

#include "CMapCell.hpp"
#include "CGlobalGame.hpp"
#include "CObjectController.hpp"
CMapCell::CMapCell(const std::shared_ptr<CObjectController> &m_unit,
                   const std::shared_ptr<CObjectController> &m_village,
                   const std::shared_ptr<CObjectController> &m_terrain)
    : m_unit(m_unit), m_village(m_village), m_terrain(m_terrain) {}
const std::shared_ptr<CUnit> &CMapCell::GetUnitObject() const {
  return std::dynamic_pointer_cast<CUnit>(m_unit->getM_view()->getM_object());
}
const std::shared_ptr<CVillage> &CMapCell::GetVillageObject() const {
  return std::dynamic_pointer_cast<CVillage>(m_village->getM_view()->getM_object());
}
const std::shared_ptr<CTerrain> &CMapCell::GetTerrainObject() const {
  return std::dynamic_pointer_cast<CTerrain>(m_village->getM_view()->getM_object());
}
void CMapCell::setM_unit(const std::shared_ptr<CObjectController> &m_unit) {
  ++CGlobalGame::CurGlobalState;
  CMapCell::m_unit = m_unit;
}
void CMapCell::setM_village(const std::shared_ptr<CObjectController> &m_village) {
  CMapCell::m_village = m_village;
}
void CMapCell::setM_terrain(const std::shared_ptr<CObjectController> &m_terrain) {
  ++CGlobalGame::CurGlobalState;
  CMapCell::m_terrain = m_terrain;
}
CMapCell::CMapCell(const std::shared_ptr<CObjectController> &m_terrain) : m_terrain(m_terrain) {

}
const std::shared_ptr<CObjectController> &CMapCell::getM_unit() const {
  return m_unit;
}
const std::shared_ptr<CObjectController> &CMapCell::getM_village() const {
  return m_village;
}
const std::shared_ptr<CObjectController> &CMapCell::getM_terrain() const {
  return m_terrain;
}

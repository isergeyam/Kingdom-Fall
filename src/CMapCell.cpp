//
// Created by sg on 18.04.18.
//

#include "CMapCell.hpp"
#include "CGlobalGame.hpp"
#include "CObjectController.hpp"
#include "CUnit.hpp"
#include "CVillage.hpp"
#include "CTerrain.hpp"
CMapCell::CMapCell(const std::shared_ptr<CObjectController> &m_unit,
                   const std::shared_ptr<CObjectController> &m_village,
                   const std::shared_ptr<CObjectController> &m_terrain)
    : m_unit(m_unit), m_village(m_village), m_terrain(m_terrain) {}
std::shared_ptr<CUnit> CMapCell::GetUnitObject() const {
  std::shared_ptr<CUnit> empty_ptr;
  if (m_unit == nullptr)
    return empty_ptr;
  else
    return  std::dynamic_pointer_cast<CUnit>(m_unit->GetPositionView()->getM_object());
}
std::shared_ptr<CVillage> CMapCell::GetVillageObject() const {
  return (m_village == nullptr) ? nullptr : std::dynamic_pointer_cast<CVillage>(m_village->GetPositionView()->getM_object());
}
std::shared_ptr<CTerrain> CMapCell::GetTerrainObject() const {
  return (m_terrain == nullptr) ? nullptr : std::dynamic_pointer_cast<CTerrain>(m_terrain->GetPositionView()->getM_object());
}
void CMapCell::setM_unit(const std::shared_ptr<CObjectController> &m_unit) {
  ++CGlobalGame::Instance()->CurGlobalState;
  CMapCell::m_unit = m_unit;
}
void CMapCell::setM_village(std::shared_ptr<CObjectController> m_village) {
  CMapCell::m_village = m_village;
}
void CMapCell::setM_terrain(const std::shared_ptr<CObjectController> &m_terrain) {
  ++CGlobalGame::Instance()->CurGlobalState;
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
const std::shared_ptr<CObjectController> &CMapCell::GetTopObject() const {
  if (m_unit!=nullptr)
    return m_unit;
  if (m_village!=nullptr)
    return m_village;
  return m_terrain;
}
bool CMapCell::EmptyCell() {
  return m_unit == nullptr;
}

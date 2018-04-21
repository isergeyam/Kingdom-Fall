//
// Created by sg on 10.03.18.
//

#include "CUnit.hpp"
#include "CGlobalGame.hpp"
CUnit::CUnit(const CurrentSerializerType &m_properties, const CPosition &position) : CObject(position, true, false, false), m_properties(m_properties) {
  m_health = m_properties["Health"];
  m_stamina = m_properties["Stamina"];
  m_exp = 0;
}
bool CUnit::CanMove(const CPosition &new_position) {
  return CurMap()[new_position].getM_unit() == nullptr &&  CalculateDistance(new_position) <= m_stamina;
}
Quantity_t CUnit::CalculateDistance(const CPosition &new_position) {
  return 0;
}
bool CUnit::MoveTo(const CPosition &new_postion) {
  if (!CanMove(new_postion))
    return false;
  CurMap()[new_postion].setM_unit(CurMap()[m_position].getM_unit());
  CurMap()[m_position].setM_unit(nullptr);
  return true;
}

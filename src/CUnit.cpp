//
// Created by sg on 10.03.18.
//

#include "CUnit.hpp"

CUnit::CUnit(const CurrentSerializerType &m_properties, const CPosition &position) : CObject(position, true, false, false), m_properties(m_properties) {
  m_health = m_properties["Health"];
  m_stamina = m_properties["Stamina"];
  m_exp = 0;
}

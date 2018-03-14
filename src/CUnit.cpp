//
// Created by sg on 10.03.18.
//

#include "CUnit.hpp"

CUnit::CUnit(const json &m_json, const CPosition &position) : CObject(position, true, false, false), m_properties(m_json) {
  m_health = m_json["Health"];
  m_stamina = m_json["Stamina"];
}

//
// Created by sg on 10.03.18.
//

#include "CUnitFactory.hpp"
CUnitFactory::CUnitFactory(json &m_race, json &m_type, json &m_custom)
    : m_race(m_race), m_type(m_type), m_custom(m_custom) {
  const json &m_default = *CGlobalSingleton::getM_default_unit();
  /*for (json::iterator iter = m_default.begin();iter!=m_default.end();++iter) {
    auto m1 = MyCompare::GetMax(m_default, m_race, iter.key());
    auto m2 = MyCompare::GetMax(m_type, m_custom, iter.key());
    m_unit[iter.key()] = MyCompare::GetMax(m1, m2, (*CGlobalSingleton::getM_field_compare())[iter.key()]);
  }*/
  m_unit["Race"] = m_race["Name"];
  m_unit["Type"] = m_type["Name"];
  for (json::iterator iter = m_default.begin();iter!=m_default.end();++iter) {
    m_unit[iter.key()] = iter.value();
    if (iter.key() == "Abilities")
      break;
    if (m_race.count(iter.key()))
      m_unit[iter.key()]*=m_race[iter.key()];
    if (m_type.count(iter.key()))
      m_unit[iter.key()]*=m_type[iter.key()];
  }
}
std::shared_ptr<CUnit> CUnitFactory::CreateUnit() {
  return std::make_shared(new CUnit(m_unit));
}

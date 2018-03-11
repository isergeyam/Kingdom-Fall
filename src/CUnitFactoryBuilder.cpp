//
// Created by sg on 10.03.18.
//

#include "CUnitFactoryBuilder.hpp"
void CUnitFactoryBuilder::setM_race(const json &m_race) {
  CUnitFactoryBuilder::m_race = m_race;
}
void CUnitFactoryBuilder::setM_type(const json &m_type) {
  CUnitFactoryBuilder::m_type = m_type;
}
template<typename T>
void CUnitFactoryBuilder::AddAttr(std::string m_attr, T m_val) {
  m_custom[m_attr]=m_val;
  return;
}
std::shared_ptr<CUnitFactory> CUnitFactoryBuilder::GetFactory() {
  return std::shared_ptr<CUnitFactory>(new CUnitFactory(m_race, m_type, m_custom));
}
void CUnitFactoryBuilder::setM_custom(const json &m_custom) {
  CUnitFactoryBuilder::m_custom = m_custom;
}

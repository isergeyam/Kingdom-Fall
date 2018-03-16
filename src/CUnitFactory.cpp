//
// Created by sg on 10.03.18.
//

#include "CUnitFactory.hpp"
#include "CUnitFactoryBuilder.hpp"
std::shared_ptr<CUnit> CUnitFactory::CreateUnit(CPosition unit_pos) {
  return std::make_shared<CUnit>(CUnit(m_unit, unit_pos));
}
CUnitFactory::CUnitFactory(const json &m_unit) : m_unit(m_unit) {}
void CUnitFactory::setM_unit(const json &m_unit) {
  CUnitFactory::m_unit = m_unit;
}
const json &CUnitFactory::getM_unit() const {
  return m_unit;
}

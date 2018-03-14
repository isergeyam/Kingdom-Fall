//
// Created by sg on 10.03.18.
//

#include "CUnitFactory.hpp"
#include "CUnitFactoryBuilder.hpp"
std::shared_ptr<CUnit> CUnitFactory::CreateUnit(CPosition unit_pos) {
  return std::make_shared(new CUnit(m_unit, unit_pos));
}
CUnitFactory::CUnitFactory(const json &m_unit) : m_unit(m_unit) {}

//
// Created by sg on 10.03.18.
//

#ifndef GAME_PROJ_CUNITFACTORY_HPP
#define GAME_PROJ_CUNITFACTORY_HPP
#include <memory>
#include "CUnit.hpp"
class CUnitFactory {
 private:
 public:
  CUnitFactory(const json &m_unit);
 private:
  json m_unit;
 public:
  const json &getM_unit() const;
 public:
  void setM_unit(const json &m_unit);
 public:
  std::shared_ptr<CUnit> CreateUnit(CPosition unit_pos);
};

#endif //GAME_PROJ_CUNITFACTORY_HPP

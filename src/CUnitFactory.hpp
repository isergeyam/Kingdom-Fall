//
// Created by sg on 10.03.18.
//

#ifndef GAME_PROJ_CUNITFACTORY_HPP
#define GAME_PROJ_CUNITFACTORY_HPP
#include <memory>
#include "CUnit.hpp"
class CUnitFactory {
 private:
  json &m_race;
 public:
  CUnitFactory(json &m_race, json &m_type, json &m_custom);
 private:
  json &m_type;
  json &m_custom;
  json m_unit;
 public:
  std::shared_ptr<CUnit> CreateUnit();
};

#endif //GAME_PROJ_CUNITFACTORY_HPP

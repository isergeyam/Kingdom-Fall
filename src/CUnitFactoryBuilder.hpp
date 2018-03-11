//
// Created by sg on 10.03.18.
//

#ifndef GAME_PROJ_CUNITFACTORYBUILDER_HPP
#define GAME_PROJ_CUNITFACTORYBUILDER_HPP

#include "CUnitFactory.hpp"
#include <nlohmann/json.hpp>
using json = nlohmann::json;
class CUnitFactoryBuilder {
private:
  json m_race;
  json m_type;
  json m_custom;
 public:
  void setM_race(const json &m_race);
  void setM_type(const json &m_type);
  void setM_custom(const json &m_custom);
public:
  template <typename T> void AddAttr(std::string, T);
  std::shared_ptr<CUnitFactory> GetFactory();
};

#endif // GAME_PROJ_CUNITFACTORYBUILDER_HPP

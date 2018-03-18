//
// Created by sg on 10.03.18.
//

#ifndef GAME_PROJ_CUNITFACTORYBUILDER_HPP
#define GAME_PROJ_CUNITFACTORYBUILDER_HPP

#include "CUnitFactory.hpp"
class CUnitFactoryBuilder {
private:
  json m_race;
  json m_type;
  json m_custom;
  json m_default;
  template <typename T>
  T UpdateField(const json &m_def, const json &m_race, const json &m_type,
                const json &m_custom, const std::string &key);

public:
  void setM_default(const json &m_default);
  void setM_race(const json &m_race);
  void setM_type(const json &m_type);
  void setM_custom(const json &m_custom);
  template <typename T> void AddAttr(std::string, T);
  std::shared_ptr<CUnitFactory> GetFactory();
  static void ExtendJson(json &j1, const json &j2);
};

#endif // GAME_PROJ_CUNITFACTORYBUILDER_HPP

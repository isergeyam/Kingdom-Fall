//
// Created by sg on 10.03.18.
//

#ifndef GAME_PROJ_CUNITFACTORYBUILDER_HPP
#define GAME_PROJ_CUNITFACTORYBUILDER_HPP

#include "CObjectFactory.hpp"
#include "CurrentSerializer.hpp"
#include "CUnit.hpp"
using CUnitFactory = CObjectFactory<CUnit>;
class CUnitFactoryBuilder {
private:
  CurrentSerializerType m_race;
  CurrentSerializerType m_type;
  CurrentSerializerType m_custom;
  CurrentSerializerType m_default;
  template <typename T>
  T UpdateField(const CurrentSerializerType &m_def, const CurrentSerializerType &m_race, const CurrentSerializerType &m_type,
                const CurrentSerializerType &m_custom, const std::string &key);

public:
  void setM_default(const CurrentSerializerType &m_default);
  void setM_race(const CurrentSerializerType &m_race);
  void setM_type(const CurrentSerializerType &m_type);
  void setM_custom(const CurrentSerializerType &m_custom);
  template <typename T> void AddAttr(std::string, T);
  std::shared_ptr<CUnitFactory> GetFactory();
  static void ExtendData(CurrentSerializerType &j1, const CurrentSerializerType &j2);
};

#endif // GAME_PROJ_CUNITFACTORYBUILDER_HPP

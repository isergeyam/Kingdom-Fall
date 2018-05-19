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
  static std::unique_ptr<CurrentSerializerType> m_default;
  template <typename T>
  T UpdateField(const CurrentSerializerType &m_def, const CurrentSerializerType &m_race, const CurrentSerializerType &m_type,
                const CurrentSerializerType &m_custom, const std::string &key);

public:
  static CurrentValidator m_race_validator;
  static CurrentValidator m_type_validator;
  void setM_race(CurrentSerializerType &&m_race);
  void setM_type(const CurrentSerializerType &m_type);
  void setM_custom(const CurrentSerializerType &m_custom);
  template <typename T> void AddAttr(std::string, T);
  std::shared_ptr<CUnitFactory> GetFactory();
  const CurrentSerializerType &getM_race() const;
  const CurrentSerializerType &getM_type() const;
  const CurrentSerializerType &getM_custom() const;
  static void ExtendData(CurrentSerializerType &j1, const CurrentSerializerType &j2);
  static const std::unique_ptr<CurrentSerializerType> &getM_default();
  static void setM_default(std::unique_ptr<CurrentSerializerType> &&m_default);
};

#endif // GAME_PROJ_CUNITFACTORYBUILDER_HPP

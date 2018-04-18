//
// Created by sg on 10.03.18.
//

#include "CUnitFactoryBuilder.hpp"
void CUnitFactoryBuilder::setM_race(const CurrentSerializerType &m_race) {
  CUnitFactoryBuilder::m_race = m_race;
}
void CUnitFactoryBuilder::setM_type(const CurrentSerializerType &m_type) {
  CUnitFactoryBuilder::m_type = m_type;
}
template <typename T>
void CUnitFactoryBuilder::AddAttr(std::string m_attr, T m_val) {
  m_custom[m_attr] = m_val;
}
void CUnitFactoryBuilder::ExtendData(CurrentSerializerType &j1, const CurrentSerializerType &j2){
  for (auto j = j2.begin(); j != j2.end(); ++j) {
    j1[j.key()] = j.value();
  }
}
std::shared_ptr<CUnitFactory> CUnitFactoryBuilder::GetFactory() {
  CurrentSerializerType m_unit;
  m_unit["Race"] = m_race["Name"];
  m_unit["Type"] = m_type["Name"];
  for (auto &&iter : {"Health", "Stamina"})
    m_unit[iter] =
        UpdateField<Quantity_t>(m_default, m_race, m_type, m_custom, iter);
  for (auto &&iter : {"Strength", "Agility"})
    m_unit[iter] =
        UpdateField<Percent_t>(m_default, m_race, m_type, m_custom, iter);
  for (auto &&iter : {"Abilities", "AutoAbilities"}) {
    m_unit[iter] = m_default[iter];
    ExtendData(m_unit[iter], m_race[iter]);
    ExtendData(m_unit[iter], m_type[iter]);
    ExtendData(m_unit[iter], m_custom[iter]);
  }
  for (auto &&iter1 : {"Patency", "Resistance", "Adaption"}) {
    for (auto iter2 = m_default[iter1].begin(); iter2 != m_default[iter1].end();
         ++iter2) {
      m_unit[iter1][iter2.key()] =
          UpdateField<Percent_t>(m_default[iter1], m_race[iter1], m_type[iter1],
                                 m_custom[iter1], iter2.key());
    }
  }
  return std::make_shared<CUnitFactory>(CUnitFactory(std::move(m_unit)));
}
void CUnitFactoryBuilder::setM_custom(const CurrentSerializerType &m_custom) {
  CUnitFactoryBuilder::m_custom = m_custom;
}
template <typename T>
T CUnitFactoryBuilder::UpdateField(const CurrentSerializerType &m_def, const CurrentSerializerType &m_race,
                                   const CurrentSerializerType &m_type, const CurrentSerializerType &m_custom,
                                   const std::string &key) {
  auto res = m_def[key].get<T>();
  if (m_race.count(key))
    res *= m_race[key].get<Percent_t>();
  if (m_type.count(key))
    res *= m_type[key].get<Percent_t>();
  if (m_custom.count(key))
    res *= m_custom[key].get<Percent_t>();
  return res;
}
void CUnitFactoryBuilder::setM_default(const CurrentSerializerType &m_default) {
  CUnitFactoryBuilder::m_default = m_default;
}

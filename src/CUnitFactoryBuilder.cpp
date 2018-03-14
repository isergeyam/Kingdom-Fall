//
// Created by sg on 10.03.18.
//

#include "CUnitFactory.hpp"
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
}
std::shared_ptr<CUnitFactory> CUnitFactoryBuilder::GetFactory() {
  const json &m_default = *CGame::getM_default_unit();
  /*for (json::iterator iter = m_default.begin();iter!=m_default.end();++iter) {
    auto m1 = MyExtension::GetMax(m_default, m_race, iter.key());
    auto m2 = MyExtension::GetMax(m_type, m_custom, iter.key());
    m_unit[iter.key()] = MyExtension::GetMax(m1, m2, (*CGame::getM_field_compare())[iter.key()]);
  }*/
  json m_unit;
  m_unit["Race"] = m_race["Name"];
  m_unit["Type"] = m_type["Name"];
  for (auto &&iter : {"Health", "Stamina", "Agility"})
    m_unit[iter] = UpdateField<Quantity_t >(m_default, m_race, m_type, m_custom, iter);
  m_unit["Strength"] = UpdateField<Percent_t >(m_default, m_race, m_type, m_custom, "Strength");
  for (auto &&iter : {"Abilities", "AutoAbilities"}) {
    m_unit[iter] = m_default[iter];
    MyExtension::extendJson(m_unit[iter], m_race[iter]);
    MyExtension::extendJson(m_unit[iter], m_type[iter]);
    MyExtension::extendJson(m_unit[iter], m_custom[iter]);
  }
  for (auto &&iter1 : {"Patency", "Resistance"}) {
    for (auto iter2 = m_default[iter1].begin();iter2!=m_default[iter2].end();++iter2)  {
      m_unit[iter1][iter2] = UpdateField(m_default[iter1], m_race[iter1], m_type[iter1], m_custom[iter1], iter2.key());
    }
  }
  /*for (json::iterator iter = m_default.begin();iter!=m_default.end();++iter) {
    m_unit[iter.key()] = iter.value();
    if (iter.key() == "Abilities")
      break;
    if (m_race.count(iter.key()))
      m_unit[iter.key()]*=m_race[iter.key()];
    if (m_type.count(iter.key()))
      m_unit[iter.key()]*=m_type[iter.key()];
  }*/
  return std::make_shared<CUnitFactory>(new CUnitFactory(m_unit));
}
void CUnitFactoryBuilder::setM_custom(const json &m_custom) {
  CUnitFactoryBuilder::m_custom = m_custom;
}
template<typename T>
T CUnitFactoryBuilder::UpdateField(const json &m_def, const json &m_race, const json &m_type, const json &m_custom, const std::__cxx11::string &key) {
  T res = m_def[key].get<T>;
  if (!m_race[key].empty())
    res *= m_race[key].get<Percent_t>();
  if (!m_type[key].empty())
    res *= m_type[key].get<Percent_t>();
  if (!m_custom[key].empty())
    res *= m_custom[key].get<Percent_t>();
  return res;
}
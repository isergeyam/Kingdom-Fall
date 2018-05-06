//
// Created by sg on 21.04.18.
//

#include "CGlobalGame.hpp"
#include "CMap.hpp"
#include "CObjectFactory.hpp"
#include "CUnitFactoryBuilder.hpp"
#include <fstream>
#include <string>
#include <iostream>
std::shared_ptr<CurrentSerializerType> CGlobalGame::Settings() {
  if (m_settings==nullptr)
    m_settings = std::make_shared<CurrentSerializerType>();
  return m_settings;
}
std::shared_ptr<CMap> &CGlobalGame::Map() {
  if (m_map==nullptr)
    m_map = std::make_shared<CMap>();
  return m_map;
}
std::random_device CGlobalGame::m_device;
std::default_random_engine CGlobalGame::m_engine(CGlobalGame::m_device());
std::uniform_real_distribution<Percent_t> CGlobalGame::m_random_percentage(0, 1);
//std::uniform_int_distribution<bool> CGlobalGame::m_random_event(0, 1); TODO
Percent_t CGlobalGame::GetRandomPercent() {
  return m_random_percentage(m_engine);
}
const Quantity_t CGlobalGame::MaxDistance;
Quantity_t CGlobalGame::CurGlobalState = 0;
void CGlobalGame::InitializeGame(const CurrentSerializerType &new_map, const CurrentSerializerType &new_settings) {
  m_map = std::make_shared<CMap>(new_map.get<vector<vector<std::string>>>());
  m_settings = std::make_shared<CurrentSerializerType>(new_settings);
}
void CGlobalGame::InitializeTerrains(const vector<CurrentSerializerType> &m_terrains) {
  for (auto &&cur_terrain : m_terrains) {
    CGlobalGame::LoadedTerrains.insert(std::make_pair(cur_terrain["Name"].get<std::string>(),
                                       CObjectFactoryValidateDecorator<CTerrain>(std::make_shared<CObjectFactory<
                                           CTerrain>>(cur_terrain))));
  }
}
void CGlobalGame::GlobalSetUp() {
  std::ifstream iValidateUnit("json/schema/Unit.json");
  std::ifstream iValidateType("json/schema/Type.json");
  std::ifstream iValidateRace("json/schema/Race.json");
  std::ifstream iValidateTerrain("json/schema/Terrain.json");
  CObjectFactoryValidateDecorator<CTerrain>::m_validator.set_schema(CurrentSerializer::Deserialize(iValidateTerrain));
  CObjectFactoryValidateDecorator<CUnit>::m_validator.set_schema(CurrentSerializer::Deserialize(iValidateUnit));
  CUnitFactoryBuilder::m_type_validator.set_schema(CurrentSerializer::Deserialize(iValidateType));
  CUnitFactoryBuilder::m_race_validator.set_schema(CurrentSerializer::Deserialize(iValidateRace));
}
std::shared_ptr<CMap> CGlobalGame::m_map;
std::shared_ptr<CurrentSerializerType> CGlobalGame::m_settings;
std::map<std::string, CObjectFactoryValidateDecorator<CTerrain>> CGlobalGame::LoadedTerrains;

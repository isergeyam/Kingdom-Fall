//
// Created by sg on 21.04.18.
//

#include "CGlobalGame.hpp"
std::shared_ptr<CurrentSerializerType> CGlobalGame::Settings() {
  if (m_settings == nullptr)
    m_settings = std::make_shared<CurrentSerializerType>();
  return m_settings;
}
std::shared_ptr<CMap> CGlobalGame::Map() {
  if (m_map == nullptr)
    m_map = std::make_shared<CMap>();
  return m_map;
}
std::random_device CGlobalGame::m_device ;
std::default_random_engine CGlobalGame::m_engine(CGlobalGame::m_device());
std::uniform_int_distribution CGlobalGame::m_random_percentage(0, 100);
Percent_t CGlobalGame::GetRandomPercent() {
  return m_random_percentage(m_engine);
}
CMap &CurMap() {
  return *CGlobalGame::Map();
}
CurrentSerializerType &CurSettings() {
  return *CGlobalGame::Settings();
}

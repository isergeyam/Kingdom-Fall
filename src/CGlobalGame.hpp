//
// Created by sg on 21.04.18.
//

#pragma once
#include "CurrentSerializer.hpp"
#include "defines.hpp"
class CMap;
class CGlobalGame {
 private:
  static std::shared_ptr<CurrentSerializerType> m_settings;
  static std::shared_ptr<CMap> m_map;
  static std::random_device m_device;
  static std::default_random_engine m_engine;
  static std::uniform_real_distribution<Percent_t > m_random_percentage;
 public:
  CGlobalGame() = delete;
  ~CGlobalGame() = delete;
  CGlobalGame(const CGlobalGame&) = delete;
  CGlobalGame& operator=(CGlobalGame&) = delete;
  static std::shared_ptr<CurrentSerializerType> Settings();
  static std::shared_ptr<CMap> Map();
  static Percent_t GetRandomPercent();
  static const Quantity_t MaxDistance = 1000000;
  static Quantity_t CurGlobalState;
  static void InitializeGame(const CurrentSerializerType &new_map, const CurrentSerializerType &new_settings);
};
inline CMap &CurMap() {
  return *CGlobalGame::Map();
}
inline CurrentSerializerType &CurSettings() {
  return *CGlobalGame::Settings();
}


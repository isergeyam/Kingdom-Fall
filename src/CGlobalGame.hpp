//
// Created by sg on 21.04.18.
//

#pragma once
#include "CurrentSerializer.hpp"
#include "defines.hpp"
#include "CTerrain.hpp"
#include "CObjectFactoryValidateDecorator.hpp"
#include <random>
#include <SDL2pp/SDL2pp.hh>
using std::vector;
class CMap;
class CGlobalGame {
 private:
  static std::shared_ptr<CurrentSerializerType> m_settings;
  static std::shared_ptr<CMap> m_map;
  static std::random_device m_device;
  static std::default_random_engine m_engine;
  static std::uniform_real_distribution<Percent_t> m_random_percentage;
  static size_t screen_width;
  static size_t screen_height;
  static std::shared_ptr<SDL2pp::Window> m_window;
  static std::shared_ptr<SDL2pp::Renderer> m_renderer;
  //static std::uniform_int_distribution<bool> m_random_event; TODO
 public:
  CGlobalGame() = delete;
  ~CGlobalGame() = delete;
  CGlobalGame(const CGlobalGame &) = delete;
  CGlobalGame &operator=(CGlobalGame &) = delete;
  static std::shared_ptr<CurrentSerializerType> Settings();
  static std::shared_ptr<CMap> &Map();
  static Percent_t GetRandomPercent();
  //static bool GetRandomEvent(); TODO
  static const Quantity_t MaxDistance = 1000000;
  static Quantity_t CurGlobalState;
  static std::map<std::string, CObjectFactoryValidateDecorator<CTerrain>> LoadedTerrains;
  static void InitializeTerrains(const vector<CurrentSerializerType> &m_terrains);
  static void InitializeGame(const CurrentSerializerType &new_map, const CurrentSerializerType &new_settings);
  static void GlobalSetUp(const std::string &);
  static size_t getScreen_width();
  static size_t getScreen_height();
  static const std::shared_ptr<SDL2pp::Renderer> &getM_renderer();
  static const std::shared_ptr<SDL2pp::Window> &getM_window();
};
inline CMap &CurMap() {
  return *CGlobalGame::Map();
}
inline CurrentSerializerType &CurSettings() {
  return *CGlobalGame::Settings();
}
inline SDL2pp::Window &CurWindow() {
  return *CGlobalGame::getM_window();
}

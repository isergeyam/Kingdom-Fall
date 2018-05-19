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
#include <istream>
using std::vector;
class CMap;
class IControllerFactory;
class CGlobalGame {
 private:
  std::unique_ptr<CMap> m_map;
  std::default_random_engine m_engine;
  std::uniform_real_distribution<Percent_t> m_random_percentage;
  size_t screen_width;
  size_t screen_height;
  std::unique_ptr<SDL2pp::Window> m_window;
  std::unique_ptr<SDL2pp::Renderer> m_renderer;
  std::unique_ptr<SDL2pp::Font> m_font;
  bool with_graphics;
  void InitSerializerVector(CurrentSerializerType &cur_settings,
                            vector<CurrentSerializerType> &objects_vector,
                            const std::string &m_field);
  void InitializeObjects(const vector<CurrentSerializerType> &m_objects);
  void GenerateUnits(vector<CurrentSerializerType> &m_races, vector<CurrentSerializerType> &m_types);
  static std::shared_ptr<CGlobalGame> m_instance;
 public:
  std::map<std::string, std::unique_ptr<IControllerFactory>> LoadedObjects;
  CGlobalGame();
  ~CGlobalGame() = default;
  CGlobalGame(const CGlobalGame &) = delete;
  void GlobalSetUp(std::istream &m_string = std::cin);
  CGlobalGame &operator=(CGlobalGame &) = delete;
  std::unique_ptr<CMap> & Map();
  inline CMap& CurMap();
  inline SDL2pp::Renderer& CurRenderer();
  inline SDL2pp::Window& CurWindow();
  Percent_t GetRandomPercent();
  static const Quantity_t MaxDistance = 1000000;
  Quantity_t CurGlobalState;
  size_t getScreen_width();
  size_t getScreen_height();
  const std::unique_ptr<SDL2pp::Renderer> & getM_renderer();
  bool isWith_graphics();
  const std::unique_ptr<SDL2pp::Window> & getM_window();
  void StartGame();
  void GlobalMessage(std::string message);
  static std::shared_ptr<CGlobalGame> Instance();
};

//
// Created by sg on 21.04.18.
//

#pragma once
#include "CObjectFactoryValidateDecorator.hpp"
#include "CTerrain.hpp"
#include "CurrentSerializer.hpp"
#include "defines.hpp"
#include <SDL2pp/SDL2pp.hh>
#include <istream>
#include <random>
using std::vector;
class CMap;
class IControllerFactory;
class CGlobalGame {
public:
  struct FontDeleter {
    void operator()(SDL2pp::Font *font_) {}
  };

private:
  std::unique_ptr<CMap> m_map;
  std::default_random_engine m_engine;
  std::uniform_real_distribution<Percent_t> m_random_percentage;
  size_t screen_width;
  size_t screen_height;
  std::unique_ptr<SDL2pp::Window> m_window;
  std::unique_ptr<SDL2pp::Renderer> m_renderer;
  std::unique_ptr<SDL2pp::Font, FontDeleter> m_font;
  std::shared_ptr<CurrentValidator> m_validate_unit;
  bool with_graphics;
  void InitSerializerVector(CurrentSerializerType &cur_settings,
                            vector<CurrentSerializerType> &objects_vector,
                            const std::string &m_field);
  void GenerateUnits(vector<CurrentSerializerType> &m_races,
                     vector<CurrentSerializerType> &m_types);
  static std::shared_ptr<CGlobalGame> m_instance;

public:
  std::map<std::string, std::unique_ptr<IControllerFactory>> LoadedObjects;
  CGlobalGame();
  ~CGlobalGame() = default;
  CGlobalGame(const CGlobalGame &) = delete;
  void GlobalSetUp(std::istream &m_string = std::cin);
  CGlobalGame &operator=(CGlobalGame &) = delete;
  std::unique_ptr<CMap> &Map();
  CMap &CurMap();
  SDL2pp::Renderer &CurRenderer();
  Percent_t GetRandomPercent();
  static const Quantity_t MaxDistance = 1000000;
  Quantity_t CurGlobalState;
  size_t getScreen_width();
  size_t getScreen_height();
  const std::unique_ptr<SDL2pp::Renderer> &getM_renderer();
  bool isWith_graphics();
  const std::unique_ptr<SDL2pp::Window> &getM_window();
  void StartGame();
  void GlobalMessage(std::string message);
  static std::shared_ptr<CGlobalGame> Instance();
  const std::shared_ptr<CurrentValidator> &getM_validate_unit() const;
  void InitializeObjects(const vector<CurrentSerializerType> &m_objects);
};

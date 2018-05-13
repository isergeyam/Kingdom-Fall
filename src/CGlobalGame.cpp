//
// Created by sg on 21.04.18.
//

#include "CGlobalGame.hpp"
#include "CMap.hpp"
#include "CUnitFactoryBuilder.hpp"
#include "CControllerFactory.hpp"
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
void CGlobalGame::InitializeObjects(const vector<CurrentSerializerType> &m_objects) {
  for (auto cur_object : m_objects) {
    std::string cur_name = cur_object["Name"].get<std::string>();
    if (cur_name.find("Terrain")!=std::string::npos) {
      std::shared_ptr<IObjectFactory> factory_ptr = std::static_pointer_cast<IObjectFactory>(std::make_shared<CObjectFactory<CTerrain> >(cur_object));
      auto controller_ptr = std::make_shared<CControllerFactory>(factory_ptr);
      //auto controller_ptr = std::make_shared<CControllerFactory>(factory_ptr);
      CGlobalGame::LoadedObjects
          .insert(std::make_pair(cur_name, controller_ptr));
    } else if (cur_name.find("Village")!=std::string::npos) {
      CGlobalGame::LoadedObjects
          .insert(std::make_pair(cur_name,
                                 std::make_unique<CControllerFactory>(std::make_shared<CObjectFactory<CVillage>>(
                                     cur_object))));
    }
  }
}
void CGlobalGame::GlobalSetUp(std::istream &m_settings) {
  CurrentSerializerType cur_settings = CurrentSerializer::Deserialize(m_settings);
  std::ifstream iValidateUnit(cur_settings["UnitValidator"].get<std::string>());
  std::ifstream iValidateType(cur_settings["TypeValidator"].get<std::string>());
  std::ifstream iValidateRace(cur_settings["RaceValidator"].get<std::string>());
  std::ifstream iValidateTerrain(cur_settings["TerrainValidator"].get<std::string>());
  std::ifstream iMap(cur_settings["Map"].get<std::string>());
  //CObjectFactoryValidateDecorator<CTerrain>::m_validator.set_schema(CurrentSerializer::Deserialize(iValidateTerrain));
  //CObjectFactoryValidateDecorator<CUnit>::m_validator.set_schema(CurrentSerializer::Deserialize(iValidateUnit));
  CUnitFactoryBuilder::m_type_validator.set_schema(CurrentSerializer::Deserialize(iValidateType));
  CUnitFactoryBuilder::m_race_validator.set_schema(CurrentSerializer::Deserialize(iValidateRace));
  std::vector<CurrentSerializerType> objects_vector;
  for (auto &it : cur_settings["objects"]) {
    std::ifstream iCurTerrain(it.get<std::string>());
    objects_vector.push_back(CurrentSerializer::Deserialize(iCurTerrain));
  }
  screen_width = cur_settings["width"].get<size_t>();
  screen_height = cur_settings["height"].get<size_t>();
  with_graphics = cur_settings["enable_graphics"].get<bool>();
  if (with_graphics) {
    m_window = std::make_shared<SDL2pp::Window>("Kingdom Fall", 0, 0, screen_width, screen_height, SDL_WINDOW_SHOWN);
    m_renderer = std::make_shared<SDL2pp::Renderer>(*m_window, -1, SDL_RENDERER_ACCELERATED);
  } else
    with_graphics = false;
  InitializeObjects(objects_vector);
  m_map = std::make_shared<CMap>(iMap);
}
size_t CGlobalGame::getScreen_width() {
  return screen_width;
}
size_t CGlobalGame::getScreen_height() {
  return screen_height;
}
const std::shared_ptr<SDL2pp::Window> &CGlobalGame::getM_window() {
  return m_window;
}
const std::shared_ptr<SDL2pp::Renderer> &CGlobalGame::getM_renderer() {
  return m_renderer;
}
bool CGlobalGame::isWith_graphics() {
  return with_graphics;
}
void CGlobalGame::StartGame() {
  CurMap().UpdateView();
  CurRenderer().Present();
  SDL_Delay(100);
}
std::shared_ptr<CMap> CGlobalGame::m_map;
std::shared_ptr<CurrentSerializerType> CGlobalGame::m_settings;
std::map<std::string, std::shared_ptr<CControllerFactory> > CGlobalGame::LoadedObjects;
std::shared_ptr<SDL2pp::Window> CGlobalGame::m_window;
std::shared_ptr<SDL2pp::Renderer> CGlobalGame::m_renderer;
size_t CGlobalGame::screen_width;
size_t CGlobalGame::screen_height;
bool CGlobalGame::with_graphics;

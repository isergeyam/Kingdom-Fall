//
// Created by sg on 21.04.18.
//

#include "CGlobalGame.hpp"
#include "CMap.hpp"
#include "CUnitFactoryBuilder.hpp"
#include "CControllerFactory.hpp"
template<typename TO, typename FROM>
std::unique_ptr<TO> static_unique_pointer_cast(std::unique_ptr<FROM> &&old) {
  return std::unique_ptr<TO>{static_cast<TO *>(old.release())};
  //conversion: unique_ptr<FROM>->FROM*->TO*->unique_ptr<TO>
}
//std::shared_ptr<CurrentSerializerType> CGlobalGame::Settings() {
//  if (m_settings==nullptr)
//    m_settings = std::make_shared<CurrentSerializerType>();
//  return m_settings;
//}
std::unique_ptr<CMap> &CGlobalGame::Map() {
  if (m_map==nullptr)
    m_map = std::make_unique<CMap>();
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
//void CGlobalGame::InitializeGame(const CurrentSerializerType &new_map, const CurrentSerializerType &new_settings) {
//  m_map = std::make_shared<CMap>(new_map.get<vector<vector<std::string>>>());
//  m_settings = std::make_shared<CurrentSerializerType>(new_settings);
//}
void CGlobalGame::InitializeObjects(const vector<CurrentSerializerType> &m_objects) {
  for (auto cur_object : m_objects) {
    std::string cur_name = cur_object["Name"].get<std::string>();
    if (cur_name.find("Terrain")!=std::string::npos) {
      std::shared_ptr<IObjectFactory> factory_ptr =
          std::static_pointer_cast<IObjectFactory>(std::make_shared<CObjectFactory<CTerrain>>(cur_object));
      auto controller_ptr =
          static_unique_pointer_cast<IControllerFactory>(std::make_unique<CControllerFactory>(factory_ptr));
      //auto controller_ptr = std::make_shared<CControllerFactory>(factory_ptr);
      CGlobalGame::LoadedObjects
          .insert(std::make_pair(cur_name, std::move(controller_ptr)));
    } else if (cur_name.find("Village")!=std::string::npos) {
      auto factory_ptr =
          std::static_pointer_cast<IObjectFactory>(std::make_shared<CObjectFactory<CVillage>>(cur_object));
      auto controller_ptr =
          static_unique_pointer_cast<IControllerFactory>(std::make_unique<CControllerFactory>(factory_ptr));
      CGlobalGame::LoadedObjects
          .insert(std::make_pair(cur_name, std::move(controller_ptr)));
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
  std::ifstream iUnitMap(cur_settings["UnitMap"].get<std::string>());
  std::ifstream iVillageMap(cur_settings["VillageMap"].get<std::string>());
  //CObjectFactoryValidateDecorator<CTerrain>::m_validator.set_schema(CurrentSerializer::Deserialize(iValidateTerrain));
  //CObjectFactoryValidateDecorator<CUnit>::m_validator.set_schema(CurrentSerializer::Deserialize(iValidateUnit));
  CUnitFactoryBuilder::m_type_validator.set_schema(CurrentSerializer::Deserialize(iValidateType));
  CUnitFactoryBuilder::m_race_validator.set_schema(CurrentSerializer::Deserialize(iValidateRace));
  std::vector<CurrentSerializerType> objects_vector;
  std::vector<CurrentSerializerType> races_vector;
  std::vector<CurrentSerializerType> types_vector;
  InitSerializerVector(cur_settings, objects_vector, "objects");
  InitSerializerVector(cur_settings, races_vector, "races");
  InitSerializerVector(cur_settings, types_vector, "types");
  screen_width = cur_settings["width"].get<size_t>();
  screen_height = cur_settings["height"].get<size_t>();
  with_graphics = cur_settings["enable_graphics"].get<bool>();
  if (with_graphics) {
    m_window =
        std::make_unique<SDL2pp::Window>("Kingdom Fall", 0, 0, screen_width + 100, screen_height, SDL_WINDOW_SHOWN);
    m_renderer = std::make_unique<SDL2pp::Renderer>(*m_window, -1, SDL_RENDERER_ACCELERATED);
  } else
    with_graphics = false;
  InitializeObjects(objects_vector);
  GenerateUnits(races_vector, types_vector);
  m_map = std::make_unique<CMap>(iMap);
  m_map->SetObjects(iVillageMap, false);
  m_map->SetObjects(iUnitMap, true);
}
void CGlobalGame::InitSerializerVector(CurrentSerializerType &cur_settings,
                                      vector<CurrentSerializerType> &objects_vector,
                                      const std::string &m_field) {
  for (auto &it : cur_settings[m_field]) {
    std::ifstream iCurObject(it.get<std::__cxx11::string>());
    objects_vector.push_back(CJsonSerializerAdapter::Deserialize(iCurObject));
  }
}
size_t CGlobalGame::getScreen_width() {
  return screen_width;
}
size_t CGlobalGame::getScreen_height() {
  return screen_height;
}
const std::unique_ptr<SDL2pp::Window> &CGlobalGame::getM_window() {
  return m_window;
}
const std::unique_ptr<SDL2pp::Renderer> &CGlobalGame::getM_renderer() {
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
void CGlobalGame::GenerateUnits(vector<CurrentSerializerType> &m_races,
                                vector<CurrentSerializerType> &m_types) {
  for (CurrentSerializerType &it_race : m_races) {
    for (CurrentSerializerType &it_type : m_types) {
      CUnitFactoryBuilder m_builder;
      m_builder.setM_race(std::move(it_race));
      m_builder.setM_type(std::move(it_type));
      CGlobalGame::LoadedObjects.insert(std::make_pair(
          m_builder.getM_race()["Name"].get<std::string>() + m_builder.getM_race()["Name"].get<std::string>(),
          static_unique_pointer_cast<IControllerFactory>(std::make_unique<CControllerFactory>(m_builder
                                                                                                  .GetFactory()))));
    }
  }
}
void CGlobalGame::GlobalMessage(const std::string &message) {
  if (!with_graphics) {
    std::cout << message << std::endl;
    return;
  }
  SDL2pp::Font font("data/Vera.ttf", 12);
  size_t start_pos = 0;
  SDL2pp::Renderer &m_renderer = CurRenderer();
  m_renderer.FillRect(SDL2pp::Rect(screen_width, 0, screen_width+100, screen_height));
  while (start_pos < message.size()) {
    std::string cur_message = message.substr(start_pos, 8);
    start_pos += 8;
    SDL2pp::Texture text_sprite(m_renderer, font.RenderText_Blended(cur_message, SDL_Color{255, 255, 255, 255}));
    m_renderer.Copy(text_sprite,
                    SDL2pp::Rect(screen_width, 12*(start_pos/8), text_sprite.GetWidth(), text_sprite.GetHeight()),
                    SDL2pp::Rect(0, 0, text_sprite.GetWidth(), text_sprite.GetHeight()));
  }
}
std::unique_ptr<CMap> CGlobalGame::m_map;
std::map<std::string, std::unique_ptr<IControllerFactory> > CGlobalGame::LoadedObjects;
std::unique_ptr<SDL2pp::Window> CGlobalGame::m_window;
std::unique_ptr<SDL2pp::Renderer> CGlobalGame::m_renderer;
size_t CGlobalGame::screen_width;
size_t CGlobalGame::screen_height;
bool CGlobalGame::with_graphics;

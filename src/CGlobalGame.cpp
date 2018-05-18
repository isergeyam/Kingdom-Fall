//
// Created by sg on 21.04.18.
//

#include "CGlobalGame.hpp"
#include "CMap.hpp"
#include "CUnitFactoryBuilder.hpp"
#include "CControllerFactory.hpp"
#include "CSelectCommand.hpp"
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
  for (auto &cur_object : m_objects) {
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
    } else throw std::invalid_argument("Object name doesn't match");
  }
}
void CGlobalGame::GlobalSetUp(std::istream &m_settings) {
  CurrentSerializerType cur_settings = CurrentSerializer::Deserialize(m_settings);
  std::ifstream iValidateUnit(cur_settings["UnitValidator"].get<std::string>());
  std::ifstream iValidateType(cur_settings["TypeValidator"].get<std::string>());
  std::ifstream iValidateRace(cur_settings["RaceValidator"].get<std::string>());
  std::ifstream iValidateTerrain(cur_settings["TerrainValidator"].get<std::string>());
  std::ifstream iDefaultUnit(cur_settings["DefaultUnit"].get<std::string>());
  std::ifstream iMap(cur_settings["Map"].get<std::string>());
  std::ifstream iUnitMap(cur_settings["UnitMap"].get<std::string>());
  std::ifstream iVillageMap(cur_settings["VillageMap"].get<std::string>());
  //CObjectFactoryValidateDecorator<CTerrain>::m_validator.set_schema(CurrentSerializer::Deserialize(iValidateTerrain));
  //CObjectFactoryValidateDecorator<CUnit>::m_validator.set_schema(CurrentSerializer::Deserialize(iValidateUnit));
  CUnitFactoryBuilder::m_type_validator.set_schema(CurrentSerializer::Deserialize(iValidateType));
  CUnitFactoryBuilder::m_race_validator.set_schema(CurrentSerializer::Deserialize(iValidateRace));
  CUnitFactoryBuilder::setM_default(std::make_unique<CurrentSerializerType>(CurrentSerializer::Deserialize(iDefaultUnit)));
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
        std::make_unique<SDL2pp::Window>("Kingdom Fall", 0, 0, screen_width + 600, screen_height, SDL_WINDOW_SHOWN);
    m_renderer = std::make_unique<SDL2pp::Renderer>(*m_window, -1, SDL_RENDERER_ACCELERATED);
  }
  InitializeObjects(objects_vector);
  GenerateUnits(races_vector, types_vector);
  m_map = std::make_unique<CMap>(iMap);
  m_map->SetObjects(iVillageMap, false);
  m_map->SetObjects(iUnitMap, true);
  m_font = std::make_unique<SDL2pp::Font>(cur_settings["font_name"].get<std::string>(),
                                          cur_settings["font_size"].get<int>());
}
void CGlobalGame::InitSerializerVector(CurrentSerializerType &cur_settings,
                                       vector<CurrentSerializerType> &objects_vector,
                                       const std::string &m_field) {
  for (auto &it : cur_settings[m_field]) {
    std::ifstream iCurObject(it.get<std::__cxx11::string>());
    objects_vector.push_back(CurrentSerializer::Deserialize(iCurObject));
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
  CurMap().RenderMap();
  CurRenderer().Present();
  SDL_Event event;
  CCommand *m_command = nullptr;
  size_t clip_width = screen_height/CurMap().getM_y_size();
  size_t clip_height = screen_width/CurMap().getM_x_size();
  while (true) {
    SDL_WaitEvent(&event);
    if (event.type==SDL_QUIT)
      break;
    if (event.type==SDL_MOUSEBUTTONUP && event.button.button==SDL_BUTTON_LEFT) {
      CurRenderer().Clear();
      auto x = event.button.y;
      auto y = event.button.x;
      if (x > screen_width)
        continue;
      CPosition command_position(x/clip_width, y/clip_height);
      std::cout << command_position.getM_x_axis() << " " << command_position.getM_y_axis() << std::endl;
      CCommand *new_command = new CSelectCommand(command_position);
      if (m_command!=nullptr) {
        if (m_command->TryAttack(new_command))
          m_command = nullptr;
        else
          m_command = new_command;
      } else {
        m_command = new_command;
        new_command->Proceed();
      }
      CurMap().RenderMap();
      CurRenderer().Present();
    } else if (event.type==SDL_KEYDOWN && event.key.keysym.sym==SDLK_SPACE) {
      GlobalMessage("New turn");
      CurMap().ToggleAbilities();
      CurMap().RenderMap();
      CurRenderer().Present();
    }
  }
}
void CGlobalGame::GenerateUnits(vector<CurrentSerializerType> &m_races,
                                vector<CurrentSerializerType> &m_types) {
  for (CurrentSerializerType &it_race : m_races) {
    for (CurrentSerializerType &it_type : m_types) {
      CUnitFactoryBuilder m_builder;
      m_builder.setM_race(std::move(it_race));
      m_builder.setM_type(it_type);
      CGlobalGame::LoadedObjects.insert(std::make_pair(
          m_builder.getM_race()["Name"].get<std::string>() + m_builder.getM_type()["Name"].get<std::string>(),
          static_unique_pointer_cast<IControllerFactory>(std::make_unique<CControllerFactory>(m_builder
                                                                                                  .GetFactory()))));
    }
  }
}
void CGlobalGame::GlobalMessage(std::string message) {
  CurRenderer().Clear();
  std::cout << message << std::endl;
  if (!with_graphics)
    return;
  SDL2pp::Renderer &m_renderer = CurRenderer();
  SDL2pp::Rect new_port_view(screen_width, 0, 600, screen_height);
  m_renderer.FillRect(new_port_view);
  m_renderer.SetViewport(new_port_view);
  std::stringstream ss(message);
  std::string token;
  size_t cur_pos = 0;
  while (std::getline(ss, token, '$')) {
    if (token.empty())
      continue;
    SDL2pp::Texture text_sprite(m_renderer, m_font->RenderText_Blended(token, SDL_Color{255, 255, 255, 255}));
    m_renderer.Copy(text_sprite,
                    SDL2pp::NullOpt,
                    SDL2pp::Rect(0, cur_pos*m_font->GetHeight(), text_sprite.GetWidth(), text_sprite.GetHeight()));
    ++cur_pos;
  }
}
std::unique_ptr<CMap> CGlobalGame::m_map;
std::map<std::string, std::unique_ptr<IControllerFactory> > CGlobalGame::LoadedObjects;
std::unique_ptr<SDL2pp::Window> CGlobalGame::m_window;
std::unique_ptr<SDL2pp::Renderer> CGlobalGame::m_renderer;
std::unique_ptr<SDL2pp::Font> CGlobalGame::m_font;
size_t CGlobalGame::screen_width;
size_t CGlobalGame::screen_height;
bool CGlobalGame::with_graphics;

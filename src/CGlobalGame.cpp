//
// Created by sg on 21.04.18.
//

#include "CGlobalGame.hpp"
#include "CControllerFactory.hpp"
#include "CMap.hpp"
#include "CSelectCommand.hpp"
#include "CUnitFactoryBuilder.hpp"
template <typename TO, typename FROM>
std::unique_ptr<TO> static_unique_pointer_cast(std::unique_ptr<FROM> &&old) {
  return std::unique_ptr<TO>{static_cast<TO *>(old.release())};
}
std::unique_ptr<CMap> &CGlobalGame::Map() {
  if (m_map == nullptr)
    m_map = std::make_unique<CMap>();
  return m_map;
}
Percent_t CGlobalGame::GetRandomPercent() {
  return m_random_percentage(m_engine);
}
void CGlobalGame::InitializeObjects(
    const vector<CurrentSerializerType> &m_objects) {
  for (auto &cur_object : m_objects) {
    std::string cur_name = cur_object["Name"].get<std::string>();
    if (cur_name.find("Terrain") != std::string::npos) {
      std::shared_ptr<IObjectFactory> factory_ptr =
          std::static_pointer_cast<IObjectFactory>(
              std::make_shared<CObjectFactory<CTerrain>>(cur_object));
      auto controller_ptr = static_unique_pointer_cast<IControllerFactory>(
          std::make_unique<CControllerFactory>(factory_ptr));
      CGlobalGame::LoadedObjects.insert(
          std::make_pair(cur_name, std::move(controller_ptr)));
    } else if (cur_name.find("Village") != std::string::npos) {
      auto factory_ptr = std::static_pointer_cast<IObjectFactory>(
          std::make_shared<CObjectFactory<CVillage>>(cur_object));
      auto controller_ptr = static_unique_pointer_cast<IControllerFactory>(
          std::make_unique<CControllerFactory>(factory_ptr));
      CGlobalGame::LoadedObjects.insert(
          std::make_pair(cur_name, std::move(controller_ptr)));
    } else
      throw std::invalid_argument("Object name doesn't match");
  }
}
void CGlobalGame::GlobalSetUp(std::istream &m_settings) {
  CurrentSerializerType cur_settings =
      CurrentSerializer::Deserialize(m_settings);
  std::ifstream iValidateUnit(cur_settings["UnitValidator"].get<std::string>());
  std::ifstream iValidateType(cur_settings["TypeValidator"].get<std::string>());
  std::ifstream iValidateRace(cur_settings["RaceValidator"].get<std::string>());
  std::ifstream iValidateTerrain(
      cur_settings["TerrainValidator"].get<std::string>());
  std::ifstream iDefaultUnit(cur_settings["DefaultUnit"].get<std::string>());
  std::ifstream iMap(cur_settings["Map"].get<std::string>());
  std::ifstream iUnitMap(cur_settings["UnitMap"].get<std::string>());
  std::ifstream iVillageMap(cur_settings["VillageMap"].get<std::string>());
  m_validate_unit = std::make_shared<CurrentValidator>();
  m_validate_unit->set_schema(CurrentSerializer::Deserialize(iValidateUnit));
  CurrentValidator m_val1, m_val2;
  m_val1.set_schema(CurrentSerializer::Deserialize(iValidateRace));
  m_val2.set_schema(CurrentSerializer::Deserialize(iValidateType));
  CUnitFactoryBuilder::m_race_validator = std::move(m_val1);
  CUnitFactoryBuilder::m_type_validator = std::move(m_val2);
  CUnitFactoryBuilder::setM_default(std::make_unique<CurrentSerializerType>(
      CurrentSerializer::Deserialize(iDefaultUnit)));
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
    m_window = std::make_unique<SDL2pp::Window>(
        "Kingdom Fall", 0, 0, screen_width + 600, screen_height,
        SDL_WINDOW_SHOWN);
    m_renderer = std::make_unique<SDL2pp::Renderer>(*m_window, -1,
                                                    SDL_RENDERER_ACCELERATED);
  }
  InitializeObjects(objects_vector);
  GenerateUnits(races_vector, types_vector);
  m_map = std::make_unique<CMap>(iMap);
  m_map->SetObjects(iVillageMap, false);
  m_map->SetObjects(iUnitMap, true);
  if (with_graphics)
    m_font = std::move(std::unique_ptr<SDL2pp::Font, FontDeleter>(
        new SDL2pp::Font(cur_settings["font_name"].get<std::string>(),
                         cur_settings["font_size"].get<int>())));
}
void CGlobalGame::InitSerializerVector(
    CurrentSerializerType &cur_settings,
    vector<CurrentSerializerType> &objects_vector, const std::string &m_field) {
  for (auto &it : cur_settings[m_field]) {
    std::ifstream iCurObject(it.get<std::__cxx11::string>());
    objects_vector.push_back(CurrentSerializer::Deserialize(iCurObject));
  }
}
size_t CGlobalGame::getScreen_width() { return screen_width; }
size_t CGlobalGame::getScreen_height() { return screen_height; }
const std::unique_ptr<SDL2pp::Window> &CGlobalGame::getM_window() {
  return m_window;
}
const std::unique_ptr<SDL2pp::Renderer> &CGlobalGame::getM_renderer() {
  return m_renderer;
}
bool CGlobalGame::isWith_graphics() { return with_graphics; }
void CGlobalGame::StartGame() {
  CurMap().RenderMap();
  CurRenderer().Present();
  SDL_Event event;
  std::shared_ptr<CCommand> m_command;
  size_t clip_width = screen_height / CurMap().getM_y_size();
  size_t clip_height = screen_width / CurMap().getM_x_size();
  while (true) {
    SDL_WaitEvent(&event);
    if (event.type == SDL_QUIT)
      break;
    else if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_ESCAPE) {
      CGlobalGame::GlobalMessage("");
      m_command = nullptr;
      CurMap().RenderMap();
      CurRenderer().Present();
    } else if (event.type == SDL_MOUSEBUTTONUP &&
               event.button.button == SDL_BUTTON_LEFT) {
      CurRenderer().Clear();
      auto x = event.button.y;
      auto y = event.button.x;
      if (x > screen_width)
        continue;
      CPosition command_position(x / clip_width, y / clip_height);
      auto new_command = std::static_pointer_cast<CCommand>(
          std::make_shared<CSelectCommand>(command_position));
      if (m_command != nullptr) {
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
    } else if (event.type == SDL_KEYDOWN &&
               event.key.keysym.sym == SDLK_SPACE) {
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
          m_builder.getM_race()["Name"].get<std::string>() +
              m_builder.getM_type()["Name"].get<std::string>(),
          static_unique_pointer_cast<IControllerFactory>(
              std::make_unique<CControllerFactory>(m_builder.GetFactory()))));
    }
  }
}
void CGlobalGame::GlobalMessage(std::string message) {
  CurRenderer().Clear();
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
    SDL2pp::Texture text_sprite(
        m_renderer,
        m_font->RenderText_Blended(token, SDL_Color{255, 255, 255, 255}));
    m_renderer.Copy(text_sprite, SDL2pp::NullOpt,
                    SDL2pp::Rect(0, cur_pos * m_font->GetHeight(),
                                 text_sprite.GetWidth(),
                                 text_sprite.GetHeight()));
    ++cur_pos;
  }
}
CGlobalGame::CGlobalGame()
    : m_engine(std::random_device()()), m_random_percentage(0, 1),
      CurGlobalState(0) {}
CMap &CGlobalGame::CurMap() { return *Map(); }
SDL2pp::Renderer &CGlobalGame::CurRenderer() { return *getM_renderer(); }
std::shared_ptr<CGlobalGame> CGlobalGame::Instance() {
  if (m_instance == nullptr)
    m_instance = std::make_shared<CGlobalGame>();
  return m_instance;
}
const std::shared_ptr<CurrentValidator> &
CGlobalGame::getM_validate_unit() const {
  return m_validate_unit;
}
const Quantity_t CGlobalGame::MaxDistance;
std::shared_ptr<CGlobalGame> CGlobalGame::m_instance;

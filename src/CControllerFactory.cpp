//
// Created by sg on 09.05.18.
//

#include "CControllerFactory.hpp"
#include "CGlobalGame.hpp"
CControllerFactory::CControllerFactory(const CurrentSerializerType &m_properties)
    : CObjectFactory(m_properties),
      m_texture(new SDL2pp::Texture(CurRenderer(), m_properties["icon"].get<std::string>())) {
}
std::shared_ptr<CObjectController> CControllerFactory::CreateController(CPosition m_pos) {
  return std::make_shared<CObjectController>(CreateObject(m_pos), m_texture);
}

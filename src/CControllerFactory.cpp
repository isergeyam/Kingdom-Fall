//
// Created by sg on 09.05.18.
//

#include "CControllerFactory.hpp"
#include "CGlobalGame.hpp"
std::shared_ptr<CObjectController> CControllerFactory::CreateController(CPosition m_pos) {
  return std::make_shared<CObjectController>(m_factory->CreateObject(m_pos), m_texture);
}
CControllerFactory::CControllerFactory(std::shared_ptr<IObjectFactory> m_copy_factory) : m_factory(std::move(m_copy_factory)) {
  m_texture =
      std::make_shared<SDL2pp::Texture>(CGlobalGame::Instance()->CurRenderer(), this->m_factory->getM_properties()["icon"].get<std::string>());
}

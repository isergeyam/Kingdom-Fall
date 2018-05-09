//
// Created by sg on 09.05.18.
//

#pragma once
#include "CObjectFactory.hpp"
#include "CObjectController.hpp"
#include <SDL2pp/SDL2pp.hh>
class CControllerFactory : public CObjectFactory {
 protected:
  std::shared_ptr<SDL2pp::Texture> m_texture;
 public:
  explicit CControllerFactory(const CurrentSerializerType &m_properties);
  std::shared_ptr<CObjectController> CreateController(CPosition m_pos);
};



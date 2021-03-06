//
// Created by sg on 09.05.18.
//

#pragma once
#include "IObjectFactory.hpp"
#include "CObjectController.hpp"
#include <SDL2pp/SDL2pp.hh>
#include "IControllerFactory.hpp"
class CControllerFactory : public IControllerFactory {
 protected:
  std::shared_ptr<SDL2pp::Texture> m_texture;
  std::shared_ptr<IObjectFactory> m_factory;
 public:
  explicit CControllerFactory(std::shared_ptr<IObjectFactory> m_copy_factory);
  std::shared_ptr<CObjectController> CreateController(CPosition m_pos) override;
};



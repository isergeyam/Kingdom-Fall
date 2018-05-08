//
// Created by sg on 08.05.18.
//

#pragma once
#include <SDL2/SDL.h>
#include "IObjectObserver.hpp"
#include "CObject.hpp"
#include "IObjectController.hpp"
class IObjectView : public IObjectObserver {
 private:
  const SDL_Texture &m_texture;
  std::shared_ptr<IObjectController> m_controller;
  CPosition prev_position;
 public:
  explicit IObjectView(const std::shared_ptr<CObject> &m_obj,
                       const std::shared_ptr<IObjectController> &m_controller,
                       const SDL_Texture &m_texture);
  void UpdateObject() override;
};



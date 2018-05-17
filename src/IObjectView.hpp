//
// Created by sg on 16.05.18.
//

#pragma once
#include "SDL2pp/SDL2pp.hh"
#include "IObjectObserver.hpp"
#include <memory>
class IObjectView : public IObjectObserver {
 public:
  virtual const std::shared_ptr<SDL2pp::Texture> &getM_texture() = 0;
  virtual void RenderObject() = 0;
  explicit IObjectView(const std::shared_ptr<CObject> &m_object_copy);
};



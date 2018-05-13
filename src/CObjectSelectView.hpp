//
// Created by sg on 13.05.18.
//

#pragma once

#include "IObjectObserver.hpp"
#include "IObjectController.hpp"
class CObjectSelectView : public IObjectObserver{
 private:
  std::shared_ptr<IObjectController> m_controller;
 public:
  void UpdateObject() override;
  const std::shared_ptr<SDL2pp::Texture> &getM_texture() override;
  CObjectSelectView(const std::shared_ptr<CObject> &m_copy_object,
                      const std::shared_ptr<IObjectController> &m_copy_controller);
};



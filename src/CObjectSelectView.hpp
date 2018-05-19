//
// Created by sg on 13.05.18.
//

#pragma once

#include <bits/stdc++.h>
#include "IObjectObserver.hpp"
#include "IObjectController.hpp"
#include "IObjectView.hpp"
#include <SDL2pp/SDL2pp.hh>
class CObjectSelectView : public IObjectView {
 private:
  IObjectController* m_controller;
  std::shared_ptr<SDL2pp::Texture> m_texture;
 public:
  void UpdateObject() override;
  const std::shared_ptr<SDL2pp::Texture> &getM_texture() override;
  CObjectSelectView(const std::shared_ptr<CObject> &m_copy_object,
                      IObjectController *m_copy_controller,
                      std::shared_ptr<SDL2pp::Texture> m_copy_texture);
  void RenderObject() override;
};



//
// Created by sg on 13.05.18.
//

#pragma once

#include <bits/stdc++.h>
#include "IObjectObserver.hpp"
#include "IObjectController.hpp"
#include "IObjectView.hpp"
class CObjectSelectView : public IObjectView {
 private:
  IObjectController* m_controller;
 public:
  void UpdateObject() override;
  const std::shared_ptr<SDL2pp::Texture> &getM_texture() override;
  CObjectSelectView(const std::shared_ptr<CObject> &m_copy_object,
                    IObjectController *m_copy_controller);
  void RenderObject() override;
};



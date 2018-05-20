//
// Created by sg on 08.05.18.
//

#pragma once
#include <SDL2pp/SDL2pp.hh>
#include <bits/stdc++.h>
#include "IObjectObserver.hpp"
#include "CObject.hpp"
#include "IObjectController.hpp"
#include "IObjectView.hpp"
class CObjectPositionView : public IObjectView {
 private:
  std::shared_ptr<SDL2pp::Texture> m_texture;
  IObjectController* m_controller;
  CPosition prev_position;
  static SDL2pp::Rect PositionRect(const CPosition &m_pos);
 public:
  explicit CObjectPositionView(const std::shared_ptr<CObject> &m_obj,
                               IObjectController *m_controller,
                               const std::shared_ptr<SDL2pp::Texture> &m_texture);
  void UpdateObject() override;
  std::shared_ptr<SDL2pp::Texture> getM_texture() override;
  IObjectController * getM_controller() const;
  const CPosition &getPrev_position() const;
  void RenderObject();
  ~CObjectPositionView() override = default;
};



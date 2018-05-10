//
// Created by sg on 08.05.18.
//

#pragma once
#include <SDL2pp/SDL2pp.hh>
#include "IObjectObserver.hpp"
#include "CObject.hpp"
#include "IObjectController.hpp"
class IObjectView : public IObjectObserver {
 private:
  std::shared_ptr<SDL2pp::Texture> m_texture;
  std::shared_ptr<IObjectController> m_controller;
  CPosition prev_position;
  static SDL2pp::Rect PositionRect(const CPosition &m_pos);
 public:
  explicit IObjectView(const std::shared_ptr<CObject> &m_obj,
                       const std::shared_ptr<IObjectController> &m_controller,
                       const std::shared_ptr<SDL2pp::Texture> &m_texture);
  void UpdateObject() override;
  const std::shared_ptr<SDL2pp::Texture> &getM_texture() const;
  const std::shared_ptr<IObjectController> &getM_controller() const;
  const CPosition &getPrev_position() const;
};



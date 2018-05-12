//
// Created by sg on 08.05.18.
//

#pragma once
#include "IObjectController.hpp"
#include "CObjectPositionView.hpp"
#include <SDL2pp/SDL2pp.hh>
class CObjectController : public IObjectController {
 private:
  std::shared_ptr<IObjectObserver> m_view;
 public:
  explicit CObjectController(const std::shared_ptr<CObject> &m_object,
                             const std::shared_ptr<SDL2pp::Texture> &m_texture);
  void SetObjectPosition(CPosition m_pos) override;
  const std::shared_ptr<IObjectObserver> & getM_view() const;
};



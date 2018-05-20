//
// Created by sg on 12.05.18.
//

#pragma once
#include "IObjectView.hpp"
class CObjectProxyView : public IObjectView {
public:
  explicit CObjectProxyView(std::shared_ptr<CObject> m_object = nullptr);
  void UpdateObject() override;
  ~CObjectProxyView() override = default;
  std::shared_ptr<SDL2pp::Texture> getM_texture() override;
  void RenderObject() override;
};

//
// Created by sg on 12.05.18.
//

#pragma once
#include "IObjectObserver.hpp"
class CObjectProxyView : public IObjectObserver {
 public:
  explicit CObjectProxyView(const std::shared_ptr<CObject> &m_object = nullptr);
  void UpdateObject() override;
};



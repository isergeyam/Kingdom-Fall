//
// Created by sg on 08.05.18.
//

#pragma once
#include "CPosition.hpp"
#include <memory>
class CObject;
class IObjectController {
 protected:
  std::shared_ptr<CObject> m_object;
 public:
  virtual void SetObjectPosition(CPosition m_pos) = 0;
  explicit IObjectController(const std::shared_ptr<CObject> &m_object);
  virtual ~IObjectController();
};



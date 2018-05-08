//
// Created by sg on 08.05.18.
//

#pragma once
#include "CPosition.hpp"
#include <bits/shared_ptr.h>
class CObject;
class IObjectController {
 private:
  std::shared_ptr<CObject> m_object;
 public:
  virtual void SetObjectPosition(CPosition m_pos) = 0;
  explicit IObjectController(std::shared_ptr<CObject> m_object);
};



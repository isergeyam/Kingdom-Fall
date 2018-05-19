//
// Created by sg on 13.05.18.
//

#pragma once

#include <bits/shared_ptr.h>
#include "CPosition.hpp"
class CObjectController;
class IControllerFactory {
 public:
  virtual std::shared_ptr<CObjectController> CreateController(CPosition m_pos) = 0;
  virtual ~IControllerFactory() = default;
};





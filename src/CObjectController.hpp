//
// Created by sg on 08.05.18.
//

#pragma once
#include "IObjectController.hpp"
#include "IObjectView.hpp"
class CObjectController : public IObjectController {
 private:
  std::shared_ptr<IObjectView> m_view;
 public:
  explicit CObjectController(std::shared_ptr<CObject> m_object);
};



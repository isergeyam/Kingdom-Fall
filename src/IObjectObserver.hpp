//
// Created by sg on 08.05.18.
//

#pragma once
#include <bits/stdc++.h>
class CObject;
class IObjectObserver {
 protected:
  std::shared_ptr<CObject> m_object;
 public:
  explicit IObjectObserver(std::shared_ptr<CObject> m_object);
  virtual void UpdateObject() = 0;
};



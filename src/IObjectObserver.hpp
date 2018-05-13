//
// Created by sg on 08.05.18.
//

#pragma once
#include <bits/stdc++.h>
#include <SDL2pp/SDL2pp.hh>
class CObject;
class IObjectObserver {
 protected:
  std::shared_ptr<CObject> m_object;
 public:
  explicit IObjectObserver(std::shared_ptr<CObject> m_object);
  virtual void UpdateObject() = 0;
  virtual const std::shared_ptr<SDL2pp::Texture> &getM_texture() = 0;
  const std::shared_ptr<CObject> &getM_object() const;
  virtual ~IObjectObserver() = default;
};



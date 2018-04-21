//
// Created by sg on 20.04.18.
//

#pragma once
#include <bits/shared_ptr.h>
#include "CPosition.hpp"
#include "CurrentSerializer.hpp"
template<typename _Object>
class IObjectFactory {
 public:
  virtual std::shared_ptr<_Object> CreateObject(const CPosition &) = 0;
  virtual const CurrentSerializerType &getM_properties() const = 0;
  virtual ~IObjectFactory() = 0;
};
template<typename _Object>
IObjectFactory<_Object>::~IObjectFactory() {}



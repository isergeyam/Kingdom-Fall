//
// Created by sg on 20.04.18.
//

#pragma once
#include <memory>
#include "CurrentSerializer.hpp"
class CObject;
class CPosition;
class IObjectFactory {
 public:
  virtual std::shared_ptr<CObject> CreateObject(const CPosition &) = 0;
  virtual const CurrentSerializerType &getM_properties() const = 0;
  virtual ~IObjectFactory() = 0;
};



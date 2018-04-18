//
// Created by sg on 18.04.18.
//

#pragma once
#include "json-validator.hpp"
#include "CPosition.hpp"
template<typename _Object>
class CObjectFactory {
 private:
  static json_validator m_validator;
  json m_properties;
 public:
  explicit CObjectFactory(json m_properties);
  std::shared_ptr<_Object> CreateObject(const CPosition &m_position);
};



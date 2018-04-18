//
// Created by sg on 18.04.18.
//

#pragma once
#include "CurrentSerializer.hpp"
#include "CPosition.hpp"
template<typename _Object>
class CObjectFactory {
 private:
  static CurrentValidator m_validator;
  CurrentSerializerType m_properties;
 public:
  explicit CObjectFactory(CurrentSerializerType m_properties);
  std::shared_ptr<_Object> CreateObject(const CPosition &m_position);
};



//
// Created by sg on 18.04.18.
//

#pragma once
#include "CurrentSerializer.hpp"
#include "CPosition.hpp"
template<typename _Object>
class CObjectFactory {
 private:
  CurrentSerializerType m_properties;
 public:
  static CurrentValidator m_validator;
  explicit CObjectFactory(CurrentSerializerType m_properties);
  const CurrentSerializerType &getM_properties() const;
  std::shared_ptr<_Object> CreateObject(const CPosition &m_position);
};
template<typename _Object>
CurrentValidator CObjectFactory<_Object>::m_validator = CurrentValidator();



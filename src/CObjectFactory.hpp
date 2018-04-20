//
// Created by sg on 18.04.18.
//

#pragma once
#include "CurrentSerializer.hpp"
#include "CPosition.hpp"
#include "IObjectFactory.hpp"
template<typename _Object>
class CObjectFactory : public IObjectFactory<_Object> {
 private:
  CurrentSerializerType m_properties;
 public:
  explicit CObjectFactory(CurrentSerializerType m_properties);
  const CurrentSerializerType &getM_properties() const;
  std::shared_ptr<_Object> CreateObject(const CPosition &m_position);
};


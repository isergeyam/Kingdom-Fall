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
  const CurrentSerializerType &getM_properties() const override;
  std::shared_ptr<_Object> CreateObject(const CPosition &m_position) override ;
  ~CObjectFactory() = default;
};
template<typename _Object>
CObjectFactory<_Object>::CObjectFactory(CurrentSerializerType m_properties) : m_properties(std::move(m_properties)) {
}
template<typename _Object>
std::shared_ptr<_Object> CObjectFactory<_Object>::CreateObject(const CPosition &m_position) {
  return std::make_shared<_Object>(m_properties, m_position);
}
template<typename _Object>
const CurrentSerializerType &CObjectFactory<_Object>::getM_properties() const {
  return m_properties;
}


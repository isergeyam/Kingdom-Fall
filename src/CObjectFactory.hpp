//
// Created by sg on 18.04.18.
//

#pragma once
#include "CurrentSerializer.hpp"
#include "CPosition.hpp"
#include "IObjectFactory.hpp"
#include "CVillage.hpp"
#include "CTerrain.hpp"
#include "CUnit.hpp"
template<typename _Object>
class CObjectFactory : public IObjectFactory {
 protected:
  CurrentSerializerType m_properties;
 public:
  explicit CObjectFactory(CurrentSerializerType m_properties);
  const CurrentSerializerType &getM_properties() const override;
  std::shared_ptr<CObject> CreateObject(const CPosition &m_position) override;
  ~CObjectFactory() override = default ;
};
template <typename _Object>
CObjectFactory<_Object>::CObjectFactory(CurrentSerializerType m_properties)
    : m_properties(std::move(m_properties)) {
}
template<typename _Object>
std::shared_ptr<CObject> CObjectFactory<_Object>::CreateObject(const CPosition &m_position) {
  return std::static_pointer_cast<CObject>(std::make_shared<_Object>(m_properties, m_position));
}
template<typename _Object>
const CurrentSerializerType &CObjectFactory<_Object>::getM_properties() const {
  return m_properties;
}

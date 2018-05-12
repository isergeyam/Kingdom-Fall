//
// Created by sg on 10.05.18.
//
#include "CObjectFactory.hpp"
template <typename _Object>
CObjectFactory<_Object>::CObjectFactory(CurrentSerializerType m_properties)
    : m_properties(std::move(m_properties)) {
}
template<typename _Object>
std::shared_ptr<CObject> CObjectFactory<_Object>::CreateObject(const CPosition &m_position) {
  return std::make_shared<_Object>(m_properties, m_position);
}
template<typename _Object>
const CurrentSerializerType &CObjectFactory<_Object>::getM_properties() const {
  return m_properties;
}

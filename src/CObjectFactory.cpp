//
// Created by sg on 18.04.18.
//

#include "CObjectFactory.hpp"
template<typename _Object>
CObjectFactory<_Object>::CObjectFactory(CurrentSerializerType m_properties):m_properties(std::move(m_properties)) {
  m_validator.validate(m_properties);
}
template<typename _Object>
std::shared_ptr<_Object> CObjectFactory<_Object>::CreateObject(const CPosition &m_position) {
  return std::make_shared<_Object>(m_position, m_properties);
}

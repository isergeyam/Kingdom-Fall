//
// Created by sg on 08.05.18.
//
#include "IObjectObserver.hpp"
#include "CObject.hpp"
IObjectObserver::IObjectObserver(const std::shared_ptr<CObject> &m_object_copy) : m_object(std::move(m_object_copy)) {
  m_object->AddObserver(this);
}
const std::shared_ptr<CObject> &IObjectObserver::getM_object() const {
  return m_object;
}

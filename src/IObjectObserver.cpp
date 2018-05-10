//
// Created by sg on 08.05.18.
//
#pragma once
#include "IObjectObserver.hpp"
IObjectObserver::IObjectObserver(std::shared_ptr<CObject> m_object) : m_object(m_object) {}
const std::shared_ptr<CObject> &IObjectObserver::getM_object() const {
  return m_object;
}

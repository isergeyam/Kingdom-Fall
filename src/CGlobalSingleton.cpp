//
// Created by sg on 11.03.18.
//
#include "CGlobalSingleton.hpp"
static std::shared_ptr<json> CGlobalSingleton::getM_default_unit() {
  return m_default_unit;
}
static std::shared_ptr<std::map<std::string, bool>> CGlobalSingleton::getM_field_compare() {
  return m_field_compare;
}


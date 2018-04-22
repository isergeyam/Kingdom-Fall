//
// Created by sg on 10.03.18.
//

#include "CTerrain.hpp"

CTerrain::CTerrain(const CurrentSerializerType &m_properties, const CPosition &m_position)
    : m_properties(m_properties), CObject(m_position, false, m_properties["Pass"], m_properties["FlyPass"]) {
  m_patency = m_properties["Patency"];
  m_name = m_properties["Name"];
}
Quantity_t CTerrain::getM_patency() const {
  return m_patency;
}
const std::string &CTerrain::getM_name() const {
  return m_name;
}

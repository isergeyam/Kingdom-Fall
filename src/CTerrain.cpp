//
// Created by sg on 10.03.18.
//

#include "CTerrain.hpp"

CTerrain::CTerrain(const CPosition &m_position,  const CurrentSerializerType &m_properties) : m_properties(m_properties), CObject(m_position, false, m_properties["DefaultPass"], m_properties["DefaultFlyPass"]) {
  m_patency = m_properties['Patency'];
  m_name = m_properties['Name'];
}
Quantity_t CTerrain::getM_patency() const {
  return m_patency;
}
const std::string &CTerrain::getM_name() const {
  return m_name;
}

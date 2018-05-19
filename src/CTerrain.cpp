//
// Created by sg on 10.03.18.
//

#include "CTerrain.hpp"

CTerrain::CTerrain(const CurrentSerializerType &m_properties,
                   const CPosition &m_position,
                   std::shared_ptr<CGlobalGame> m_game)
    : CObject(m_position,
              false,
              m_properties["Pass"],
              m_properties["FlyPass"],
              false,
              m_properties,
              std::move(m_game)) {
  m_patency = m_properties["Patency"];
  m_name = m_properties["Name"];
}
Quantity_t CTerrain::getM_patency() const {
  return m_patency;
}
const std::string &CTerrain::getM_name() const {
  return m_name;
}
std::string CTerrain::GetInfo() {
  return "Name: " + m_properties["Name"].get<std::string>() + "$" + "Pass: " + std::to_string(isPassable()) + "$"
      + "Fly pass: " + std::to_string(isFly_passable());
}

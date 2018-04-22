//
// Created by sg on 10.03.18.
//

#ifndef GAME_PROJ_CFIELD_HPP
#define GAME_PROJ_CFIELD_HPP

#include "CObject.hpp"
#include "CurrentSerializer.hpp"
#include <string>
#include <vector>
class CTerrain : public CObject {
private:
  const CurrentSerializerType &m_properties;
  Quantity_t m_patency;
  std::string m_name;
 public:
  Quantity_t getM_patency() const;
  const std::string &getM_name() const;
  CTerrain(const CurrentSerializerType &m_properties, const CPosition &m_position);
};

#endif // GAME_PROJ_CFIELD_HPP

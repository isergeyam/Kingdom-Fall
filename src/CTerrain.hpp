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
  CTerrain(const CPosition &m_position, const CurrentSerializerType &m_properties);
};

#endif // GAME_PROJ_CFIELD_HPP

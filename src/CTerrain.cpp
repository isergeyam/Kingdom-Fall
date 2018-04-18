//
// Created by sg on 10.03.18.
//

#include "CTerrain.hpp"

CTerrain::CTerrain(const CPosition &m_position,  const CurrentSerializerType &m_properties) : m_properties(m_properties), CObject(m_position, false, m_properties["DefaultPass"], m_properties["DefaultFlyPass"]) {

}

//
// Created by sg on 16.04.18.
//

#include "CTerrainFactory.hpp"
CTerrainFactory::CTerrainFactory(const json &m_field) : m_field(m_field) {
  m_validator.validate(m_field);
}
std::shared_ptr<CTerrain> CTerrainFactory::CreateField(const CPosition &field_position) {
  return std::make_shared<CTerrain>(field_position, m_field);
}

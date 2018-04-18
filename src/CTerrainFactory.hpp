//
// Created by sg on 16.04.18.
//

#pragma once
#include "CTerrain.hpp"
#include "json-validator.hpp"
class CTerrainFactory {
 private:
  json m_field;
  static json_validator m_validator;
 public:
  explicit CTerrainFactory(const json &m_field);
  std::shared_ptr<CTerrain> CreateField(const CPosition &field_position);
};



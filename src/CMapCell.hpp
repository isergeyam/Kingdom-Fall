//
// Created by sg on 18.04.18.
//

#pragma once
#include "CObject.hpp"
#include "CTerrain.hpp"
#include <memory>
#include <vector>
class CMapCell {
 private:
  std::vector<std::shared_ptr<CObject>> m_objects;
  CTerrain m_terrain;
 public:
  explicit CMapCell(CTerrain m_terrain);
};



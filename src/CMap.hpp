//
// Created by sg on 18.04.18.
//

#pragma once
#include <set>
#include "CMapCell.hpp"
class CMap {
 private:
  std::set<CPosition, CMapCell> m_map;
};



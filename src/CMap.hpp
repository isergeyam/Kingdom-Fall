//
// Created by sg on 18.04.18.
//

#pragma once
#include "CMapCell.hpp"
using std::vector;
class CMap {
 private:
  vector<vector<CMapCell>> m_map;
 public:
  CMapCell & operator[](const CPosition &m_pos);
};



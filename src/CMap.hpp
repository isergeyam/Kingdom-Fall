//
// Created by sg on 18.04.18.
//

#pragma once
#include "CMapCell.hpp"
using std::vector;
class CMap {
 private:
  vector<vector<CMapCell>> m_map;
  Quantity_t m_state = 0;
  Quantity_t m_x_size;
  Quantity_t m_y_size;
  friend class CMapCell;'
 public:
  CMapCell & operator[](const CPosition &m_pos);
  Quantity_t getM_state() const;
  Quantity_t getM_x_size() const;
  Quantity_t getM_y_size() const;
  Quantity_t PosToInt(const CPosition &pos);
  vector<CPosition> GetNeighbour(const CPosition &pos);
};



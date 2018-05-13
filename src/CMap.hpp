//
// Created by sg on 18.04.18.
//

#pragma once
#include "CMapCell.hpp"
using std::vector;
class CMap {
 private:
  vector<vector<CMapCell>> m_map;
  Quantity_t m_x_size;
  Quantity_t m_y_size;
  friend class CMapCell;
  void init(const vector<vector<std::string>> &start_terrain);
 public:
  CMap() = default;
  explicit CMap(const vector<vector<std::string>> &start_terrain);
  explicit CMap(std::istream &stream_);
  CMapCell & operator[](const CPosition &m_pos);
  Quantity_t getM_x_size() const;
  Quantity_t getM_y_size() const;
  Quantity_t PosToInt(const CPosition &pos);
  vector<CPosition> GetNeighbour(const CPosition &pos);
  void UpdateView();
  void SetObjects(std::istream &is, bool units);
};



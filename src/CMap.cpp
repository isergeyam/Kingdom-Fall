//
// Created by sg on 18.04.18.
//

#include "CMap.hpp"
CMapCell & CMap::operator[](const CPosition &m_pos) {
  return m_map[m_pos.getM_x_axis()][m_pos.getM_y_axis()];
}
Quantity_t CMap::getM_x_size() const {
  return m_x_size;
}
Quantity_t CMap::getM_y_size() const {
  return m_y_size;
}
Quantity_t CMap::PosToInt(const CPosition &pos) {
  return m_x_size*pos.getM_x_axis() + pos.getM_y_axis();
}
vector<CPosition> CMap::GetNeighbour(const CPosition &pos) {
  vector<CPosition> ans;
  for (int x=-1;x<=1;++x) {
    for (int y=-1;y<=1;++y) {
      int nx = pos.getM_x_axis()+x;
      int ny = pos.getM_y_axis()+y;
      if (nx<0 || ny<0 || nx>=m_x_size || ny>=m_x_size)
        continue;
      ans.push_back(CPosition(nx, ny));
    }
  }
  return ans;
}
CMap::CMap(vector<vector<CMapCell>> m_map) : m_map(std::move(m_map)) {
  m_x_size = m_map.size();
  m_y_size = m_map[0].size();
}

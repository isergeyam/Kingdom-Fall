//
// Created by sg on 18.04.18.
//

#include "CMap.hpp"
#include "CGlobalGame.hpp"
#include <fstream>
#include <sstream>
CMapCell &CMap::operator[](const CPosition &m_pos) {
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
  for (int x = -1; x <= 1; ++x) {
    for (int y = -1; y <= 1; ++y) {
      int nx = pos.getM_x_axis() + x;
      int ny = pos.getM_y_axis() + y;
      if (nx < 0 || ny < 0 || nx >= m_x_size || ny >= m_y_size)
        continue;
      ans.push_back(CPosition(nx, ny));
    }
  }
  return ans;
}
CMap::CMap(const vector<vector<std::string>> &start_terrains) {
  init(start_terrains);
}
CMap::CMap(std::ifstream &stream_) {
  vector<vector<std::string>> m_terrains;
  while(!stream_.eof()) {
    std::string cur_terrains;
    std::getline(stream_, cur_terrains);
    vector<std::string> tokens;
    std::istringstream current_iss(cur_terrains);
    std::copy(std::istream_iterator<std::string>(current_iss), std::istream_iterator<std::string>(), std::back_inserter(tokens));
    m_terrains.push_back(std::move(tokens));
  }
  init(m_terrains);
}
void CMap::init(const vector<vector<std::string>> &start_terrains) {
  m_map.resize(start_terrains.size());
  std::fill(m_map.begin(), m_map.end(), vector<CMapCell>(start_terrains[0].size()));
  m_x_size = start_terrains.size();
  m_y_size = start_terrains[0].size();
  for(size_t i=0;i<m_x_size;++i) {
    for (size_t j=0;j<m_y_size;++j) {
      m_map[i][j] = CMapCell(CGlobalGame::LoadedTerrains[start_terrains[i][j]].CreateObject(CPosition(i, j)));
    }
  }
  ++CGlobalGame::CurGlobalState;
}
void CMap::UpdateFieldView(CPosition m_pos) {
  CMapCell cur_cell = operator[](m_pos);
  if (cur_cell.getM_terrain() != nullptr) {

  }
}

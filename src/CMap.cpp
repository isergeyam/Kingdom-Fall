//
// Created by sg on 18.04.18.
//

#include "CMap.hpp"
#include "CGlobalGame.hpp"
#include <fstream>
#include <sstream>
#include "CControllerFactory.hpp"
#include "CUnit.hpp"
#include "CVillage.hpp"
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
CMap::CMap(std::istream &stream_) {
  vector<vector<std::string>> m_terrains;
  while(!stream_.eof()) {
    std::string cur_terrains;
    std::getline(stream_, cur_terrains);
    vector<std::string> tokens;
    std::istringstream current_iss(cur_terrains);
    std::copy(std::istream_iterator<std::string>(current_iss), std::istream_iterator<std::string>(), std::back_inserter(tokens));
    if (tokens.empty())
      break;
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
      m_map[i][j] = CMapCell(CGlobalGame::LoadedObjects[start_terrains[i][j]]->CreateController(CPosition(i, j)));
    }
  }
  ++CGlobalGame::CurGlobalState;
}
void CMap::RenderMap() {
  for (auto &it1 : m_map) {
    for (auto &it2 : it1) {
      it2.getM_terrain()->GetPositionView()->RenderObject();
      it2.GetTerrainObject()->setHighlighted(false);
      it2.GetTerrainObject()->setSelected(false);
      if (it2.getM_village() != nullptr) {
        it2.getM_village()->GetPositionView()->RenderObject();
        it2.GetVillageObject()->setHighlighted(false);
        it2.GetVillageObject()->setSelected(false);
      }
      if (it2.getM_unit() != nullptr) {
        it2.getM_unit()->GetPositionView()->RenderObject();
        it2.GetUnitObject()->setHighlighted(false);
        it2.GetUnitObject()->setSelected(false);
      }
    }
  }
}
void CMap::SetObjects(std::istream &is, bool units) {
  size_t i=0;
  while(!is.eof()) {
    std::string cur_terrains;
    std::getline(is, cur_terrains);
    vector<std::string> tokens;
    std::istringstream current_iss(cur_terrains);
    std::copy(std::istream_iterator<std::string>(current_iss), std::istream_iterator<std::string>(), std::back_inserter(tokens));
    for (size_t j=0;j<tokens.size();++j) {
      if (tokens[j] == ".")
        continue;
      if (units) {
        m_map[i][j].setM_unit(CGlobalGame::LoadedObjects[tokens[j]]->CreateController(CPosition(i, j)));
      } else
        m_map[i][j].setM_village(CGlobalGame::LoadedObjects[tokens[j]]->CreateController(CPosition(i, j)));
    }
    ++i;
  }
}
void CMap::ToggleAbilities() {
  for (auto &it1 : m_map) {
    for (auto &it2 : it1) {
      if (it2.GetTerrainObject()!=nullptr)
        it2.GetTerrainObject()->ToggleAutoAbilities();
      if (it2.GetVillageObject()!=nullptr)
        it2.GetVillageObject()->ToggleAutoAbilities();
      if (it2.GetUnitObject()!=nullptr)
        it2.GetUnitObject()->ToggleAutoAbilities();
    }
  }
}

//
// Created by sg on 10.03.18.
//

#include "CUnit.hpp"
#include <queue>
#include "CGlobalGame.hpp"
#include "CMap.hpp"
#include "CTerrain.hpp"
#include "CVillage.hpp"
CUnit::CUnit(const CurrentSerializerType &m_properties, const CPosition &position) : CObject(position, true, false, false), m_properties(m_properties) {
  m_health = m_properties["Health"];
  m_stamina = m_properties["Stamina"];
  m_exp = 0;
  m_state = 0;
}
bool CUnit::CanMove(const CPosition &new_position) {
  return CurMap()[new_position].getM_unit() == nullptr &&  CalculateDistance(new_position) <= m_stamina;
}
Quantity_t CUnit::CalculateDistance(const CPosition &calc_position) {
  // TODO
//  if (m_state == CurMap().getM_state())
//    return m_distances[calc_position.getM_x_axis()][calc_position.getM_y_axis()];
  m_distances.resize(CurMap().getM_x_size());
  std::fill(m_distances.begin(), m_distances.end(), vector<Quantity_t>(CurMap().getM_y_size(), CGlobalGame::MaxDistance));
  std::priority_queue<std::pair<Quantity_t, CPosition > > m_queue;
  vector<Quantity_t> m_dists(CurMap().getM_x_size()*CurMap().getM_y_size());
  m_queue.push(std::make_pair(0, m_position));
  while(!m_queue.empty()) {
    auto m_cur_vert = m_queue.top();
    m_queue.pop();
    if (m_cur_vert.first != m_distances[m_cur_vert.second.getM_x_axis()][m_cur_vert.second.getM_y_axis()])
      continue;
    for (auto &&n_vert : CurMap().GetNeighbour(m_cur_vert.second)) {
      Quantity_t  n_dist = m_cur_vert.first + CalculateDistance(CurMap()[n_vert]);
      Quantity_t &p_dist = m_distances[n_vert.getM_x_axis()][n_vert.getM_y_axis()];
      if (p_dist > n_dist) {
        p_dist = n_dist;
        m_queue.push(std::make_pair(n_dist, n_vert));
      }
    }
  }
  return m_distances[calc_position.getM_x_axis()][calc_position.getM_y_axis()];
}
bool CUnit::MoveTo(const CPosition &new_postion) {
  if (!CanMove(new_postion))
    return false;
  CurMap()[new_postion].setM_unit(CurMap()[m_position].getM_unit());
  CurMap()[m_position].setM_unit(nullptr);
  return true;
}
Quantity_t CUnit::CalculateDistance(const CMapCell &calc_position) {
  if (calc_position.getM_unit() != nullptr)
    return CGlobalGame::MaxDistance;
  CTerrain &cur_terrain = *calc_position.getM_terrain();
  return m_properties['Patency'][cur_terrain.getM_name()].get<Percent_t >()*cur_terrain.getM_patency();
}

//
// Created by sg on 10.03.18.
//

#include "CUnit.hpp"
#include "CGlobalGame.hpp"
#include "CMap.hpp"
#include "CObjectController.hpp"
CUnit::CUnit(const CurrentSerializerType &m_properties, const CPosition &position) : CObject(position,
                                                                                             true,
                                                                                             false,
                                                                                             false,
                                                                                             true,
                                                                                             m_properties) {
  m_health = m_properties["Health"];
  m_stamina = m_properties["Stamina"];
  m_exp = 0;
  m_state = 0;
}
bool CUnit::CanMove(const CPosition &new_position) {
  return CurMap()[new_position].GetUnitObject()==nullptr && CalculateDistance(new_position) <= m_stamina;
}
Quantity_t CUnit::CalculateDistance(const CPosition &calc_position) {
  if (m_state==CGlobalGame::CurGlobalState)
    return m_distances[calc_position.getM_x_axis()][calc_position.getM_y_axis()];
  m_distances.resize(CurMap().getM_x_size());
  std::fill(m_distances.begin(),
            m_distances.end(),
            vector<Quantity_t>(CurMap().getM_y_size(), CGlobalGame::MaxDistance));
  m_distances[m_position.getM_x_axis()][m_position.getM_y_axis()] = 0;
  std::vector<std::vector<CPosition >> m_prev(m_distances.size(), std::vector<CPosition>(m_distances[0].size()));
  //m_prev[m_position.getM_x_axis()][m_position.getM_y_axis()] = m_position;
  std::priority_queue<std::pair<Quantity_t, CPosition> > m_queue;
  m_queue.push(std::make_pair(0, m_position));
  while (!m_queue.empty()) {
    auto m_cur_vert = m_queue.top();
    m_queue.pop();
    if (m_cur_vert.first!=m_distances[m_cur_vert.second.getM_x_axis()][m_cur_vert.second.getM_y_axis()])
      continue;
    for (auto &&n_vert : CurMap().GetNeighbour(m_cur_vert.second)) {
      Quantity_t n_dist = m_cur_vert.first + CalculateDistance(CurMap()[n_vert]);
      Quantity_t &p_dist = m_distances[n_vert.getM_x_axis()][n_vert.getM_y_axis()];
      if (p_dist > n_dist) {
        p_dist = n_dist;
        m_queue.push(std::make_pair(n_dist, n_vert));
        //m_prev[n_vert.getM_x_axis()][n_vert.getM_y_axis()] = m_cur_vert.second;
      }
    }
  }
  m_state = CGlobalGame::CurGlobalState;
  /*vector<CPosition> m_out_prev;
  CPosition cur_pos = calc_position;
  while(m_prev[cur_pos.getM_x_axis()][cur_pos.getM_y_axis()] != cur_pos) {
    std::cout << cur_pos.getM_x_axis() << " " << cur_pos.getM_y_axis() << std::endl;
    cur_pos = m_prev[cur_pos.getM_x_axis()][cur_pos.getM_y_axis()];
  }*/
  return m_distances[calc_position.getM_x_axis()][calc_position.getM_y_axis()];
}
CObject::MoveProp CUnit::MoveTo(CPosition new_postion) {
  if (CurMap()[new_postion].GetTopObject()->GetObject()->isInjurable()
      && abs(new_postion.getM_x_axis() - m_position.getM_x_axis()) <= 1
      && abs(new_postion.getM_x_axis() - m_position.getM_y_axis()) <= 1)
    return ATTACK;
  if (!CanMove(new_postion))
    return FAIL;
  CurMap()[new_postion].setM_unit(CurMap()[m_position].getM_unit());
  CurMap()[m_position].setM_unit(nullptr);
  m_position = new_postion;
  NotifyObservers();
  return MOVE;
}
Quantity_t CUnit::CalculateDistance(const CMapCell &calc_position) {
  CTerrain &cur_terrain = *calc_position.GetTerrainObject();
  if (calc_position.GetUnitObject()!=nullptr || !cur_terrain.isPassable())
    return CGlobalGame::MaxDistance;
  return cur_terrain.getM_patency()/m_properties["Patency"][cur_terrain.getM_name()].get<Percent_t>();
}
bool CUnit::Attack(CUnit &m_other, const std::string &attack_type) {
  const auto &it = m_properties["Abilities"].find(attack_type);
  for (Quantity_t i=0;i<it["count"].get<Quantity_t >();++i)
    Hit(m_other, it);
  NotifyObservers();
  return true;
}
Quantity_t CUnit::Hit(CUnit &m_other, const CurrentSerializerType &attack_type) {
  Percent_t HitProbability = CalcHitProbability(m_other);
  if (HitProbability < CGlobalGame::GetRandomPercent())
    return 0;
  Quantity_t hit_strength = CalcHitStrength(m_other, attack_type);
  m_other.m_health -= std::min(m_other.m_health, hit_strength);
  return hit_strength;
}
Quantity_t CUnit::CalcHitStrength(const CUnit &m_other, const CurrentSerializerType &attack_type) const {
  return
      attack_type["strength"].get<Quantity_t>()
          *(1 - m_other.m_properties["Resistance"][attack_type["weapon_type"].get<std::string>()].get<Percent_t>());
}
Percent_t CUnit::CalcHitProbability(const CUnit &m_other) {
  return 1
      - m_other.m_properties["Adoption"][CurMap()[m_other.m_position].GetTerrainObject()->getM_name()].get<Percent_t>();
}

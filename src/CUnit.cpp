//
// Created by sg on 10.03.18.
//

#include "CUnit.hpp"
#include "CGlobalGame.hpp"
#include "CMap.hpp"
#include "CObjectController.hpp"
CUnit::CUnit(const CurrentSerializerType &m_properties, const CPosition &position) : CObject(position, true, false, false, true, m_properties) {
  m_health = m_properties["Health"];
  m_stamina = m_properties["Stamina"];
  m_exp = 0;
  m_state = 0;
}
bool CUnit::CanMove(const CPosition &new_position) {
  return CGlobalGame::Instance()->CurMap()[new_position].EmptyCell() && CalculateDistance(new_position) <= m_stamina;
}
Quantity_t CUnit::CalculateDistance(const CPosition &calc_position) {
  if (m_state==CGlobalGame::Instance()->CurGlobalState)
    return m_distances[calc_position.getM_x_axis()][calc_position.getM_y_axis()];
  m_distances.resize(CGlobalGame::Instance()->CurMap().getM_x_size());
  std::fill(m_distances.begin(),
            m_distances.end(),
            vector<Quantity_t>(CGlobalGame::Instance()->CurMap().getM_y_size(), CGlobalGame::Instance()->MaxDistance));
  m_distances[m_position.getM_x_axis()][m_position.getM_y_axis()] = 0;
  std::priority_queue<std::pair<Quantity_t, CPosition> > m_queue;
  m_queue.push(std::make_pair(0, m_position));
  while (!m_queue.empty()) {
    auto m_cur_vert = m_queue.top();
    m_queue.pop();
    if (m_cur_vert.first!=m_distances[m_cur_vert.second.getM_x_axis()][m_cur_vert.second.getM_y_axis()])
      continue;
    for (auto &&n_vert : CGlobalGame::Instance()->CurMap().GetNeighbour(m_cur_vert.second)) {
      Quantity_t n_dist = m_cur_vert.first + CalculateDistance(CGlobalGame::Instance()->CurMap()[n_vert]);
      Quantity_t &p_dist = m_distances[n_vert.getM_x_axis()][n_vert.getM_y_axis()];
      if (p_dist > n_dist) {
        p_dist = n_dist;
        m_queue.push(std::make_pair(n_dist, n_vert));
        //m_prev[n_vert.getM_x_axis()][n_vert.getM_y_axis()] = m_cur_vert.second;
      }
    }
  }
  m_state = CGlobalGame::Instance()->CurGlobalState;
  return m_distances[calc_position.getM_x_axis()][calc_position.getM_y_axis()];
}
CObject::MoveProp CUnit::MoveTo(CPosition new_postion) {
  if (CGlobalGame::Instance()->CurMap()[new_postion].GetTopObject()->GetObject()->isInjurable()
      && abs((int) new_postion.getM_x_axis() - (int) m_position.getM_x_axis()) <= 1
      && abs((int) new_postion.getM_y_axis() - (int) m_position.getM_y_axis()) <= 1
      && m_stamina!=0) {
    return ATTACK;
  }
  if (!CanMove(new_postion)) {
    CGlobalGame::Instance()->GlobalMessage("Can't move to that point");
    return FAIL;
  }
  m_stamina -= CalculateDistance(new_postion);
  CGlobalGame::Instance()->CurMap()[new_postion].setM_unit(CGlobalGame::Instance()->CurMap()[m_position].getM_unit());
  CGlobalGame::Instance()->CurMap()[m_position].setM_unit(nullptr);
  m_position = new_postion;
  NotifyObservers();
  return MOVE;
}
Quantity_t CUnit::CalculateDistance(const CMapCell &calc_position) {
  CTerrain &cur_terrain = *calc_position.GetTerrainObject();
  if (calc_position.GetUnitObject()!=nullptr || !cur_terrain.isPassable())
    return CGlobalGame::Instance()->MaxDistance;
  return cur_terrain.getM_patency()/m_properties["Patency"][cur_terrain.getM_name()].get<Percent_t>();
}
bool CUnit::Attack(CUnit &m_other, const std::string &attack_type) {
  m_stamina = 0;
  const auto &it = *m_properties["Abilities"].find(attack_type);
  std::string message;
  for (Quantity_t i = 0; i < it["count"].get<Quantity_t>(); ++i) {
    Quantity_t strength = Hit(m_other, it);
    message += "Hit number " + std::to_string(i + 1) + ", strength - " + std::to_string(strength) + "$";
  }
  CGlobalGame::Instance()->GlobalMessage(message);
  return true;
}
Quantity_t CUnit::Hit(CUnit &m_other, const CurrentSerializerType &attack_type) {
  Percent_t HitProbability = CalcHitProbability(m_other);
  if (HitProbability < CGlobalGame::Instance()->GetRandomPercent())
    return 0;
  Quantity_t hit_strength = CalcHitStrength(m_other, attack_type);
  m_other.m_health -= std::min(m_other.m_health, hit_strength);
  if (m_other.m_health==0)
    m_other.Die();
  return hit_strength;
}
Quantity_t CUnit::CalcHitStrength(const CUnit &m_other, const CurrentSerializerType &attack_type) const {
  return
      attack_type["strength"].get<Quantity_t>()
          *(1 - m_other.m_properties["Resistance"][attack_type["weapon_type"].get<std::string>()].get<Percent_t>());
}
Percent_t CUnit::CalcHitProbability(const CUnit &m_other) {
  return 1
      - m_other.m_properties["Adaption"][CGlobalGame::Instance()->CurMap()[m_other.m_position].GetTerrainObject()->getM_name()]
          .get<Percent_t>();
}
std::string CUnit::GetInfo() {
  return "Name: " + m_properties["Name"].get<std::string>() + "$" + "Health: " + std::to_string(m_health) + "$" + "XP: "
      + std::to_string(m_exp) + "$" + "Stamina: " + std::to_string(m_stamina) + "$" + "Current Defense: "
      + std::to_string((int) (
          m_properties["Adaption"][CGlobalGame::Instance()->CurMap()[m_position].GetTerrainObject()->getM_name()].get<Percent_t>()
              *100));
}
void CUnit::ToggleAutoAbilities() {
  for (auto &&it : m_properties["AutoAbilities"]) {
    auto cur_name = it["type"].get<std::string>();
    if (cur_name=="Refresh") {
      m_stamina = m_properties["Stamina"].get<Quantity_t>();
    } else if (cur_name=="Heal") {
      m_health = std::min(m_properties["Health"].get<Quantity_t>(), m_health + it["power"].get<Quantity_t>());
    }
  }
}
void CUnit::setM_health(Quantity_t m_health) {
  CUnit::m_health = std::min(m_properties["health"].get<Quantity_t>(), m_health);
}
Quantity_t CUnit::getM_health() const {
  return m_health;
}
void CUnit::ToggleSelected() {
  CObject::ToggleSelected();
  for (int i = 0; i < CGlobalGame::Instance()->CurMap().getM_x_size(); ++i) {
    for (int j = 0; j < CGlobalGame::Instance()->CurMap().getM_y_size(); ++j) {
      CPosition cur_pos(i, j);
      auto cur_terrain = CGlobalGame::Instance()->CurMap()[cur_pos].GetTerrainObject();
      cur_terrain->setHighlighted(CanMove(cur_pos));
      cur_terrain->NotifyObservers();
    }
  }
}

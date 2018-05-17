//
// Created by sg on 10.03.18.
//

#include "CObject.hpp"

CObject::CObject(const CPosition &m_position,
                 bool is_injurable,
                 bool is_passable,
                 bool is_fly_passable,
                 bool is_movable,
                 const CurrentSerializerType &m_prop)
    : m_properties(m_prop), m_position(m_position), injurable(is_injurable), passable(is_passable),
      fly_passable(is_fly_passable), movable(is_movable), selected(false), dead(false) {}
const CPosition &CObject::getM_position() const { return m_position; }
bool CObject::isInjurable() const { return injurable; }
bool CObject::isPassable() const { return passable; }
bool CObject::isFly_passable() const { return fly_passable; }
void CObject::setM_position(const CPosition &m_position) {
  CObject::m_position = m_position;
}
CObject::~CObject() {}
void CObject::AddObserver(IObjectObserver *m_observer) {
  m_observer_list.insert(m_observer);
}
void CObject::NotifyObservers() {
  for (auto &&it : m_observer_list)
    it->UpdateObject();
}
void CObject::RemoveObserver(IObjectObserver *m_observer) {
  m_observer_list.erase(m_observer);
}
void CObject::ToggleSelected() {
  highlighted = true;
  selected = true;
  NotifyObservers();
  selected = false;
}
bool CObject::isMovable() const {
  return movable;
}
CObject::MoveProp CObject::MoveTo(CPosition m_pos) {
  return FAIL;
}
bool CObject::Attack(CUnit &m_other, const std::string &attack_type) {
  return false;
}
const CurrentSerializerType &CObject::getM_properties() const {
  return m_properties;
}
bool CObject::isDead() const {
  return dead;
}
void CObject::Die() {
  dead = true;
  NotifyObservers();
}
void CObject::ToggleAutoAbilities() {

}
bool CObject::isHighlighted() const {
  return highlighted;
}

//
// Created by sg on 10.03.18.
//

#include "CObject.hpp"

CObject::CObject(const CPosition &m_position, bool is_injurable, bool is_passable, bool is_fly_passable) : m_position(
    m_position), injurable(is_injurable), passable(is_passable), fly_passable(is_fly_passable) {}
const CPosition &CObject::getM_position() const {
  return m_position;
}
bool CObject::isInjurable() const {
  return injurable;
}
bool CObject::isPassable() const {
  return passable;
}
bool CObject::isFly_passable() const {
  return fly_passable;
}
void CObject::setM_position(const CPosition &m_position) {
  CObject::m_position = m_position;
}

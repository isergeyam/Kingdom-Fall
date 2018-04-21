//
// Created by sg on 10.03.18.
//
#pragma once

#ifndef GAME_PROJ_CUNIT_HPP
#define GAME_PROJ_CUNIT_HPP

#include "CObject.hpp"
#include "CurrentSerializer.hpp"
#include "CMapCell.hpp"
using std::vector
class CUnit : public CObject {
public:
  explicit CUnit(const CurrentSerializerType &, const CPosition &);
  Quantity_t CalculateDistance(const CPosition &calc_position);
  Quantity_t CalculateDistance(const CMapCell &calc_position);
  bool CanMove(const CPosition &new_position);
  bool MoveTo(const CPosition &new_postion);
private:
  Quantity_t m_health;
  Quantity_t m_stamina;
  Quantity_t m_exp;
  Quantity_t m_state;
  vector<vector<Quantity_t >> m_distances;
  //std::string m_master;
  const CurrentSerializerType &m_properties;
};

#endif // GAME_PROJ_CUNIT_HPP

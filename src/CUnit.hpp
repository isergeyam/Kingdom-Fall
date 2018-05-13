//
// Created by sg on 10.03.18.
//
#pragma once

#ifndef GAME_PROJ_CUNIT_HPP
#define GAME_PROJ_CUNIT_HPP

#include "CObject.hpp"
#include "CurrentSerializer.hpp"
#include "CMapCell.hpp"
using std::vector;
class CUnit : public CObject {
public:
  explicit CUnit(const CurrentSerializerType &, const CPosition &);
  Quantity_t CalculateDistance(const CPosition &calc_position);
  Quantity_t CalculateDistance(const CMapCell &calc_position);
  bool CanMove(const CPosition &new_position);
  MoveProp MoveTo(CPosition new_postion) override;
  bool Attack(const CUnit &m_other, const std::string &attack_type) override ;
private:
  Quantity_t m_health;
  Quantity_t m_stamina;
  Quantity_t m_exp;
  Quantity_t m_state;
  vector<vector<Quantity_t >> m_distances;
  Quantity_t Hit(CUnit &m_other, const CurrentSerializerType &attack_type);
  Percent_t CalcHitProbability(const CUnit &m_other);
  //std::string m_master;
  const CurrentSerializerType &m_properties;
  Quantity_t CalcHitStrength(const CUnit &m_other, const CurrentSerializerType &attack_type) const;
};

#endif // GAME_PROJ_CUNIT_HPP

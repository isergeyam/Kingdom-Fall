//
// Created by sg on 10.03.18.
//
#pragma once

#ifndef GAME_PROJ_CUNIT_HPP
#define GAME_PROJ_CUNIT_HPP

#include "CObject.hpp"
class CUnit : public CObject {
public:
  /*struct Ability_t {
    Strength_t m_stregth;
    Percent_t m_agility;
    bool is_ranged;
    size_t m_hit_count;
  };*/
  explicit CUnit(const json&, const CPosition&);
private:
  Quantity_t m_health;
  Quantity_t m_stamina;
  //Quantity_t m_agility;
  //Percent_t m_strength;
  /*std::string m_race;
  std::string m_type;*/
  json &m_properties;
  /*json m_patency;
  json m_ability;
  json m_resistance;*/
};

#endif // GAME_PROJ_CUNIT_HPP

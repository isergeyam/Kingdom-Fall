//
// Created by sg on 10.03.18.
//
#pragma once

#ifndef GAME_PROJ_CUNIT_HPP
#define GAME_PROJ_CUNIT_HPP

#include "CObject.hpp"
#include "CurrentSerializer.hpp"
class CUnit : public CObject {
public:
  explicit CUnit(const CurrentSerializerType &, const CPosition &);

private:
  Quantity_t m_health;
  Quantity_t m_stamina;
  Quantity_t m_exp;
  //std::string m_master;
  const CurrentSerializerType &m_properties;
};

#endif // GAME_PROJ_CUNIT_HPP

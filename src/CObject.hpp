//
// Created by sg on 10.03.18.
//
#pragma once

#ifndef GAME_PROJ_OBJECT_HPP
#define GAME_PROJ_OBJECT_HPP

#include "CPosition.hpp"
#include "defines.hpp"
#include "json.hpp"
class CObject {
protected:
  CPosition m_position;
  bool injurable;
  bool passable;
  bool fly_passable;

public:
  void setM_position(const CPosition &m_position);
  CObject(const CPosition &m_position, bool is_injurable, bool is_passable,
          bool is_fly_passable);
  const CPosition &getM_position() const;
  bool isInjurable() const;
  bool isPassable() const;
  bool isFly_passable() const;
  virtual ~CObject() = 0;
};

#endif // GAME_PROJ_OBJECT_H

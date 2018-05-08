//
// Created by sg on 10.03.18.
//
#pragma once

#ifndef GAME_PROJ_OBJECT_HPP
#define GAME_PROJ_OBJECT_HPP

#include "CPosition.hpp"
#include "defines.hpp"
#include "IObjectObserver.hpp"
#include <unordered_set>
#include <bits/shared_ptr.h>
class CObject {
protected:
  CPosition m_position;
  bool injurable;
  bool passable;
  bool fly_passable;
  std::unordered_set<IObjectObserver*> m_observer_list;
public:
  void setM_position(const CPosition &m_position);
  CObject(const CPosition &m_position, bool is_injurable, bool is_passable,
          bool is_fly_passable);
  const CPosition &getM_position() const;
  bool isInjurable() const;
  bool isPassable() const;
  bool isFly_passable() const;
  void NotifyObservers();
  void AddObserver(IObjectObserver *m_observer);
  void RemoveObserver(IObjectObserver *m_observer);
  virtual ~CObject() = 0;
};

#endif // GAME_PROJ_OBJECT_H

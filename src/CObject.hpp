//
// Created by sg on 10.03.18.
//
#pragma once

#ifndef GAME_PROJ_OBJECT_HPP
#define GAME_PROJ_OBJECT_HPP

#include "CPosition.hpp"
#include "defines.hpp"
#include "IObjectObserver.hpp"
#include "CurrentSerializer.hpp"
#include <unordered_set>
#include <bits/shared_ptr.h>
class CGlobalGame;
class CUnit;
class CObject {
  //std::string m_master;
 protected:
  CPosition m_position;
  bool injurable;
  bool passable;
  bool fly_passable;
  bool movable;
  bool selected;
  bool highlighted;
  std::unordered_set<IObjectObserver *> m_observer_list;
  const CurrentSerializerType &m_properties;
  bool dead;
  std::shared_ptr<CGlobalGame> m_global_game;
 public:
  enum MoveProp {
    MOVE, ATTACK, FAIL
  };
  void setM_position(const CPosition &m_position);
  CObject(const CPosition &m_position,
            bool is_injurable,
            bool is_passable,
            bool is_fly_passable,
            bool is_movable,
            const CurrentSerializerType &m_prop,
            std::shared_ptr<CGlobalGame> m_global_game);
  const CPosition &getM_position() const;
  bool isInjurable() const;
  bool isPassable() const;
  bool isFly_passable() const;
  bool isMovable() const;
  void NotifyObservers();
  void AddObserver(IObjectObserver *m_observer);
  void RemoveObserver(IObjectObserver *m_observer);
  virtual MoveProp MoveTo(CPosition m_pos);
  virtual void ToggleSelected();
  virtual void ToggleAutoAbilities();
  virtual bool Attack(CUnit &m_other, const std::string &attack_type);
  const CurrentSerializerType &getM_properties() const;
  virtual std::string GetInfo() = 0;
  virtual ~CObject() = 0;
  bool isDead() const;
  void setHighlighted(bool highlighted);
  void setSelected(bool selected);
  bool isSelected() const;
  bool isHighlighted() const;
  void Die() ;
};

#endif // GAME_PROJ_OBJECT_H

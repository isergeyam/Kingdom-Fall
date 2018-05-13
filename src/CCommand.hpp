//
// Created by sg on 13.05.18.
//

#pragma once
#include "CMapCell.hpp"
class CCommand {
 protected:
  CPosition m_pos;
 public:
  virtual ~CCommand() = default;
  virtual void Proceed() = 0;
  virtual void Undo() = 0;
  explicit CCommand(CPosition m_pos_copy);
  virtual void SetNext(CCommand *next) = 0;
};



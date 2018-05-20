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
  virtual bool TryAttack(std::shared_ptr<CCommand> next) = 0;
  const CPosition &getM_pos() const;
};



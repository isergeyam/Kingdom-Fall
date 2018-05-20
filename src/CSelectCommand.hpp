//
// Created by sg on 13.05.18.
//

#pragma once
#include "CCommand.hpp"
class CSelectCommand : public CCommand {
 public:
  explicit CSelectCommand(CPosition m_pos_copy);
  void Proceed() override;
  void Undo() override;
  bool TryAttack(std::shared_ptr<CCommand> next) override;
};



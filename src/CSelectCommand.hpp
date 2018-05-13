//
// Created by sg on 13.05.18.
//

#pragma once
#include "CCommand.hpp"
class CSelectCommand : public CCommand {
  explicit CSelectCommand(CPosition m_pos_copy);
 public:
  void Proceed() override;
  void Undo() override;
  void SetNext(CCommand *next) override;
};



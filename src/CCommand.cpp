//
// Created by sg on 13.05.18.
//

#include "CCommand.hpp"
CCommand::CCommand(CPosition m_pos_copy) : m_pos(m_pos_copy) {}
const CPosition &CCommand::getM_pos() const {
  return m_pos;
}

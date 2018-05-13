//
// Created by sg on 13.05.18.
//

#include "CSelectCommand.hpp"
#include "CGlobalGame.hpp"
#include "CObjectController.hpp"
#include "CMap.hpp"
CSelectCommand::CSelectCommand(CPosition m_pos_copy) : CCommand(m_pos_copy) {

}
void CSelectCommand::Proceed() {
  auto cur_obj = CurMap()[m_pos].GetTopObject()->GetObject();
  cur_obj->ToggleSelected();
}
void CSelectCommand::Undo() {
  // TODO
}
void CSelectCommand::SetNext(CCommand *next) {
  auto cur_obj = CurMap()[m_pos].GetTopObject()->GetObject();
  if (cur_obj->isMovable()) {
    auto res = cur_obj->MoveTo(next->m_pos);
  }
  else
    next->Proceed();
}

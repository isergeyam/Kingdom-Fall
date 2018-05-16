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
void CSelectCommand::TryAttack(CCommand *next) {
  auto cur_obj = CurMap()[m_pos].GetTopObject()->GetObject();
  if (m_pos == next->getM_pos())
    return;
  if (cur_obj->isMovable()) {
    auto res = cur_obj->MoveTo(next->getM_pos());
    if (res==CObject::MoveProp::ATTACK) {
      const CurrentSerializerType &cur_ser = cur_obj->getM_properties();
      std::string message = "Choose attack type:$";
      std::map<int, std::string> m_map;
      int was = 1;
      for (auto &&it : cur_ser["Abilities"]) {
        if (it["type"]=="attack") {
          auto attack_name = it["Name"].get<std::string>();
          message +=
              std::to_string(was) + " - " + attack_name + " " + std::to_string(it["strength"].get<int>())
                  + "-" + std::to_string(it["count"].get<int>()) + "$";
          m_map.insert(std::make_pair(was, attack_name));
          ++was;
        }
      }
      CGlobalGame::GlobalMessage(message);
      SDL_Event event;
      while (SDL_PollEvent(&event)) {
        if (event.type==SDL_KEYDOWN) {
          wchar_t code = event.key.keysym.sym;
          if (!std::isdigit(code) || code >= was)
            CGlobalGame::GlobalMessage(message + "$Invalid code given");
          CUnit &m_other = *CurMap()[next->getM_pos()].GetUnitObject().get();
          cur_obj->Attack(m_other, m_map[was]);
          break;
        } else if (event.type==SDL_QUIT)
          exit(0);
        SDL_Delay(1);
      }
    }
  } else {
    next->Proceed();
  }
}

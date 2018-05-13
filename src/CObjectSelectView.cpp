//
// Created by sg on 13.05.18.
//

#include "CObjectSelectView.hpp"
#include "CurrentSerializer.hpp"
#include "CObject.hpp"
#include "CGlobalGame.hpp"
void CObjectSelectView::UpdateObject() {
  CGlobalGame::GlobalMessage(m_object->GetInfo());
}
const std::shared_ptr<SDL2pp::Texture> &CObjectSelectView::getM_texture() {
  return nullptr;
}
CObjectSelectView::CObjectSelectView(const std::shared_ptr<CObject> &m_copy_object,
                                     const std::shared_ptr<IObjectController> &m_copy_controller)
    : IObjectObserver(m_copy_object), m_controller(m_copy_controller) {}

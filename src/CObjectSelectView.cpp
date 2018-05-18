//
// Created by sg on 13.05.18.
//

#include "CObjectSelectView.hpp"
#include "CurrentSerializer.hpp"
#include "CObject.hpp"
#include "CGlobalGame.hpp"
void CObjectSelectView::UpdateObject() {
  if (m_object->isSelected())
    CGlobalGame::GlobalMessage(m_object->GetInfo());
  if (m_object->isHighlighted()) {
    m_texture->SetColorMod(125, 125, 125);
  } else {
    m_texture->SetColorMod();
  }
}
const std::shared_ptr<SDL2pp::Texture> &CObjectSelectView::getM_texture() {
  return m_texture;
}
CObjectSelectView::CObjectSelectView(const std::shared_ptr<CObject> &m_copy_object,
                                     IObjectController *m_copy_controller,
                                     std::shared_ptr<SDL2pp::Texture> m_copy_texture)
    : IObjectView(m_copy_object), m_controller(m_copy_controller), m_texture(std::move(m_copy_texture)) {}
void CObjectSelectView::RenderObject() {
}

//
// Created by sg on 13.05.18.
//

#include "CObjectSelectView.hpp"
#include "CurrentSerializer.hpp"
#include "CObject.hpp"
#include "CGlobalGame.hpp"
void CObjectSelectView::UpdateObject() {
  //std::cout << "Update select on " << m_object->GetInfo() << " " << m_object->isSelected() << "  " << m_object->isHighlighted() << std::endl;
  if (m_object->isSelected())
    CGlobalGame::Instance()->GlobalMessage(m_object->GetInfo());
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

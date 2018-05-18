//
// Created by sg on 08.05.18.
//

#include "CObjectPositionView.hpp"
#include "CGlobalGame.hpp"
#include "CMap.hpp"
#include "CObjectController.hpp"
CObjectPositionView::CObjectPositionView(const std::shared_ptr<CObject> &m_obj,
                                         IObjectController *m_controller,
                                         const std::shared_ptr<SDL2pp::Texture> &m_texture)
    : IObjectView(m_obj),
      m_controller(m_controller),
      prev_position(std::numeric_limits<size_t>::max(), std::numeric_limits<size_t>::max()),
      m_texture(m_texture) {}
void CObjectPositionView::UpdateObject() {
  CPosition new_position = m_object->getM_position();
  if (m_object->isDead())
    CurMap()[new_position].setM_unit(nullptr);
}
SDL2pp::Rect CObjectPositionView::PositionRect(const CPosition &m_pos) {
  size_t clip_width = CGlobalGame::getScreen_width()/CurMap().getM_y_size();
  size_t clip_height = CGlobalGame::getScreen_height()/CurMap().getM_x_size();
  return SDL2pp::Rect(clip_width*m_pos.getM_y_axis(), clip_height*m_pos.getM_x_axis(), clip_width, clip_height);
}
const std::shared_ptr<SDL2pp::Texture> &CObjectPositionView::getM_texture() {
  return m_texture;
}
IObjectController *CObjectPositionView::getM_controller() const {
  return m_controller;
}
const CPosition &CObjectPositionView::getPrev_position() const {
  return prev_position;
}
void CObjectPositionView::RenderObject() {
  SDL2pp::Rect m_rect = PositionRect(m_object->getM_position());
  CurRenderer().SetViewport(m_rect);
  CurRenderer().Copy(*m_texture);
}

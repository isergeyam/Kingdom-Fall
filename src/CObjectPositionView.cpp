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
  if (prev_position==m_object->getM_position())
    return;
  if (prev_position.getM_x_axis()==std::numeric_limits<size_t>::max())
    prev_position = new_position;
  auto prev_rect = PositionRect(prev_position);
  auto new_rect = PositionRect(new_position);
  CMapCell &prev_cell = CurMap()[prev_position];
  CMapCell &new_cell = CurMap()[new_position];
  CurRenderer().SetViewport(prev_rect);
  CurRenderer()
      .Copy(*prev_cell.getM_terrain()->GetPositionView()->getM_texture());
  if (prev_cell.getM_village()!=nullptr)
    CurRenderer()
        .Copy(*prev_cell.getM_village()->GetPositionView()->getM_texture());
  CurRenderer().SetViewport(new_rect);
  CurRenderer().Copy(*m_texture);
}
SDL2pp::Rect CObjectPositionView::PositionRect(const CPosition &m_pos) {
  size_t cell_width = CGlobalGame::getScreen_width()/CurMap().getM_x_size();
  size_t cell_height = CGlobalGame::getScreen_height()/CurMap().getM_y_size();
  return SDL2pp::Rect(cell_width*m_pos.getM_x_axis(), cell_height*m_pos.getM_y_axis(), cell_width, cell_height);
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

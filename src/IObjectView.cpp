//
// Created by sg on 08.05.18.
//

#include "IObjectView.hpp"
#include "CGlobalGame.hpp"
#include "CMap.hpp"
IObjectView::IObjectView(const std::shared_ptr<CObject> &m_obj,
                         const std::shared_ptr<IObjectController> &m_controller,
                         const std::shared_ptr<SDL2pp::Texture> &m_texture)
    : IObjectObserver(m_obj), m_controller(m_controller), prev_position(-1, -1), m_texture(m_texture) {
  m_obj->AddObserver(this);
}
void IObjectView::UpdateObject() {
  CPosition new_position = m_object->getM_position();
  if (prev_position == m_object->getM_position())
    return;
  auto prev_rect = PositionRect(prev_position);
  auto new_rect = PositionRect(new_position);
  CurRenderer().FillRect(prev_rect);
}
SDL2pp::Rect IObjectView::PositionRect(const CPosition &m_pos) {
  size_t cell_width = CGlobalGame::getScreen_width()/CurMap().getM_x_size();
  size_t cell_height = CGlobalGame::getScreen_height()/CurMap().getM_y_size();
  return SDL2pp::Rect(cell_width*m_pos.getM_x_axis(), cell_height*m_pos.getM_y_axis(), cell_width, cell_height);
}

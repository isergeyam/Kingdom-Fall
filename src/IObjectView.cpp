//
// Created by sg on 08.05.18.
//

#include "IObjectView.hpp"
#include "CGlobalGame.hpp"
IObjectView::IObjectView(const std::shared_ptr<CObject> &m_obj,
                         const std::shared_ptr<IObjectController> &m_controller,
                         const std::shared_ptr<SDL2pp::Texture> &m_texture)
    : IObjectObserver(m_obj), m_controller(m_controller), prev_position(-1, -1), m_texture(m_texture) {
  m_obj->AddObserver(this);
}
void IObjectView::UpdateObject() {
  if (prev_position == m_object->getM_position())
    return;
}

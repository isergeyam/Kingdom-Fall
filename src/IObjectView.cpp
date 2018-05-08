//
// Created by sg on 08.05.18.
//

#include "IObjectView.hpp"
IObjectView::IObjectView(const std::shared_ptr<CObject> &m_obj,
                         const std::shared_ptr<IObjectController> &m_controller,
                         const SDL_Texture &m_texture)
    : IObjectObserver(m_obj), m_controller(m_controller), prev_position(-1, -1), m_texture(m_texture) {

}
void IObjectView::UpdateObject() {
  if (prev_position == m_object->getM_position())
    return;
}

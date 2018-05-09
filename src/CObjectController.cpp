//
// Created by sg on 08.05.18.
//

#include "CObjectController.hpp"
CObjectController::CObjectController(const std::shared_ptr<CObject> &m_object,
                                     const std::shared_ptr<SDL2pp::Texture> &m_texture) : IObjectController(m_object) {
  m_view = std::make_shared<IObjectView>(m_object, std::shared_ptr<IObjectController>(this), m_texture);
}
void CObjectController::SetObjectPosition(CPosition m_pos) {
  m_object->setM_position(m_pos);
}

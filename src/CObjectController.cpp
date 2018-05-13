//
// Created by sg on 08.05.18.
//

#include "CObjectController.hpp"
#include "CGlobalGame.hpp"
#include "CObjectProxyView.hpp"
#include "CObjectSelectView.hpp"
CObjectController::CObjectController(const std::shared_ptr<CObject> &m_object,
                                     const std::shared_ptr<SDL2pp::Texture> &m_texture) : IObjectController(m_object) {
  if (CGlobalGame::isWith_graphics()) {
    m_position_view = std::static_pointer_cast<IObjectObserver>(std::make_shared<CObjectPositionView>(m_object,
                                                                                                      std::shared_ptr<
                                                                                                          IObjectController>(
                                                                                                          this),
                                                                                                      m_texture));
    m_select_view = std::static_pointer_cast<IObjectObserver>(std::make_shared<CObjectSelectView>(m_object,
                                                                                                  std::shared_ptr<
                                                                                                      IObjectController>(
                                                                                                      this)));
  } else {
    m_position_view = std::static_pointer_cast<IObjectObserver>(std::make_shared<CObjectProxyView>());
    m_select_view = std::static_pointer_cast<IObjectObserver>(std::make_shared<CObjectProxyView>());
  }
}
void CObjectController::SetObjectPosition(CPosition m_pos) {
  m_object->setM_position(m_pos);
}
const std::shared_ptr<IObjectObserver> &CObjectController::GetPositionView() const {
  return m_position_view;
}
const std::shared_ptr<CObject> &CObjectController::GetObject() const {
  return m_position_view->getM_object();
}

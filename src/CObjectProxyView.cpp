//
// Created by sg on 12.05.18.
//

#include "CObjectProxyView.hpp"
void CObjectProxyView::UpdateObject() {

}
CObjectProxyView::CObjectProxyView(const std::shared_ptr<CObject> &m_object) : IObjectObserver(m_object) {}
const std::shared_ptr<SDL2pp::Texture> &CObjectProxyView::getM_texture() {
  return nullptr;
}

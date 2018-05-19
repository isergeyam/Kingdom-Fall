//
// Created by sg on 12.05.18.
//

#include "CObjectProxyView.hpp"
void CObjectProxyView::UpdateObject() {

}
CObjectProxyView::CObjectProxyView(std::shared_ptr<CObject> m_object) : IObjectView(std::move(m_object)) {}
const std::shared_ptr<SDL2pp::Texture> &CObjectProxyView::getM_texture() {
  return nullptr;
}
void CObjectProxyView::RenderObject() {}

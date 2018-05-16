//
// Created by sg on 16.05.18.
//

#include "IObjectView.hpp"
IObjectView::IObjectView(const std::shared_ptr<CObject> &m_object_copy) : IObjectObserver(m_object_copy) {}

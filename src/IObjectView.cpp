//
// Created by sg on 16.05.18.
//

#include "IObjectView.hpp"
IObjectView::IObjectView(std::shared_ptr<CObject> m_object_copy) : IObjectObserver(std::move(m_object_copy)) {}

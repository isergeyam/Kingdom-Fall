//
// Created by sg on 10.03.18.
//

#include "CObject.h"

CObject::CObject(const CPosition &m_position, bool is_movable, bool is_injurable) : m_position(m_position),
                                                                                    is_movable(is_movable),
                                                                                    is_injurable(is_injurable) {}

CObject::CObject() {}

//
// Created by sg on 10.03.18.
//

#include "CUnit.hpp"

CUnit::CUnit(const CPosition &m_position, bool is_movable, bool is_injurable, Health_t life) : CObject(m_position,
                                                                                                       is_movable,
                                                                                                       is_injurable),
                                                                                               life(life) {}

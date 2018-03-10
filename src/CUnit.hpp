//
// Created by sg on 10.03.18.
//

#ifndef GAME_PROJ_CUNIT_HPP
#define GAME_PROJ_CUNIT_HPP


#include "CObject.h"

class CUnit : CObject {
private:
    Health_t life;
public:
    CUnit(const CPosition &m_position, bool is_movable, bool is_injurable, Health_t life);
};


#endif //GAME_PROJ_CUNIT_HPP

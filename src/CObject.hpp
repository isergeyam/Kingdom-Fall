//
// Created by sg on 10.03.18.
//

#ifndef GAME_PROJ_OBJECT_H
#define GAME_PROJ_OBJECT_H

#include "CPosition.hpp"
#include "CGlobalSingleton.hpp"
class CObject {
private:
    CPosition m_position;
    //bool is_movable;
    bool is_injurable;
    bool is_passable;
    bool is_fly_passable;
    //icon_t m_icon;
};

#endif // GAME_PROJ_OBJECT_H

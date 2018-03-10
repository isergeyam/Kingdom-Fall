//
// Created by sg on 10.03.18.
//

#ifndef GAME_PROJ_OBJECT_H
#define GAME_PROJ_OBJECT_H

#include "CPosition.h"
typedef size_t Health_t;
class CObject {
private:
    CPosition m_position;
    bool is_movable;
    bool is_injurable;
public:
    CObject(const CPosition &m_position, bool is_movable, bool is_injurable);

    CObject();
};


#endif //GAME_PROJ_OBJECT_H

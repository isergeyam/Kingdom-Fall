//
// Created by sg on 10.03.18.
//

#ifndef GAME_PROJ_POSITION_H
#define GAME_PROJ_POSITION_H

#include <cstddef>

typedef size_t Position_t;
class CPosition {
public:
    Position_t X_Axis;
    Position_t Y_Axis;

    CPosition(Position_t X_Axis, Position_t Y_Axis);

    CPosition();
};


#endif //GAME_PROJ_POSITION_H

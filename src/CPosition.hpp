//
// Created by sg on 10.03.18.
//

#ifndef GAME_PROJ_POSITION_H
#define GAME_PROJ_POSITION_H

#include "defines.hpp"
class CPosition {
private:
 public:
  CPosition(Position_t m_x_axis, Position_t m_y_axis);
  Position_t getM_x_axis() const;
  Position_t getM_y_axis() const;
 private:
  Position_t m_x_axis;
  Position_t m_y_axis;
};


#endif //GAME_PROJ_POSITION_H

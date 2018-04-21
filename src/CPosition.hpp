//
// Created by sg on 10.03.18.
//

#ifndef GAME_PROJ_POSITION_H
#define GAME_PROJ_POSITION_H

#include "defines.hpp"
class CPosition {
private:
 public:
  explicit CPosition(Position_t m_x_axis = 0, Position_t m_y_axis = 0);
  Position_t getM_x_axis() const;
  Position_t getM_y_axis() const;
  bool operator<(const CPosition &rhs) const;
  bool operator>(const CPosition &rhs) const;
  bool operator<=(const CPosition &rhs) const;
  bool operator>=(const CPosition &rhs) const;
  bool operator==(const CPosition &rhs) const;
  bool operator!=(const CPosition &rhs) const;
 private:
  Position_t m_x_axis;
  Position_t m_y_axis;
};


#endif //GAME_PROJ_POSITION_H

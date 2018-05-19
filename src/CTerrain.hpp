//
// Created by sg on 10.03.18.
//

#ifndef GAME_PROJ_CFIELD_HPP
#define GAME_PROJ_CFIELD_HPP

#include "CObject.hpp"
#include "CurrentSerializer.hpp"
#include <string>
#include <vector>
class CTerrain : public CObject {
private:
  Quantity_t m_patency;
  std::string m_name;
 public:
  Quantity_t getM_patency() const;
  const std::string &getM_name() const;
  CTerrain(const CurrentSerializerType &m_prop,
             const CPosition &m_position,
             std::shared_ptr<CGlobalGame> m_game);
  std::string GetInfo() override;
};

#endif // GAME_PROJ_CFIELD_HPP

//
// Created by sg on 10.03.18.
//

#ifndef GAME_PROJ_CFIELD_HPP
#define GAME_PROJ_CFIELD_HPP

#include "CObject.hpp"
#include <nlohmann/json.hpp>
#include <string>
#include <vector>
class CField : public CObject {
private:
  std::string m_name;

public:
  static std::map<std::string, json> EFields;
};

#endif // GAME_PROJ_CFIELD_HPP

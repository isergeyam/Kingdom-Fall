//
// Created by sg on 10.03.18.
//

#ifndef GAME_PROJ_CGLOBALSINGLETON_HPP
#define GAME_PROJ_CGLOBALSINGLETON_HPP

#include <memory>
#include "json.hpp"
#include <map>
#include "defines.hpp"
class CGame {
 private:
  static std::shared_ptr<json> m_default_unit;
  //static std::shared_ptr<std::map<std::string, bool>> m_field_compare;
 public:
  CGame() = delete;
  ~CGame() = delete;
  CGame(const CGame&) = delete;
  CGame& operator=(const CGame&) = delete;
  static std::shared_ptr<json> getM_default_unit();
  //static std::shared_ptr<std::map<std::string, bool>> getM_field_compare();
};
#endif //GAME_PROJ_CGLOBALSINGLETON_HPP

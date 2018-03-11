//
// Created by sg on 10.03.18.
//

#ifndef GAME_PROJ_CGLOBALSINGLETON_HPP
#define GAME_PROJ_CGLOBALSINGLETON_HPP

#include <memory>
#include <nlohmann/json.hpp>
#include <map>
#include "defines.hpp"
class CGlobalSingleton {
 private:
  static std::shared_ptr<json> m_default_unit;
  static std::shared_ptr<std::map<std::string, bool>> m_field_compare;
 public:
  CGlobalSingleton() = delete;
  ~CGlobalSingleton() = delete;
  CGlobalSingleton(const CGlobalSingleton&) = delete;
  CGlobalSingleton& operator=(const CGlobalSingleton&) = delete;
  static std::shared_ptr<json> getM_default_unit();
  static std::shared_ptr<std::map<std::string, bool>> getM_field_compare();
};
void extendJson(json &j1, const json &j2) {
  for (const auto &j : j2) {
    j1[j.key()] = j.value();
  }
  return;
}
namespace MyCompare{
/*template<typename T>
class Compare{
 public:
  virtual bool operator() (const T&, const T&) =0;
};
template<typename T>
class less : public Compare<T>{
 public:
  virtual bool operator() (const T& lhs, const T& rhs) {
    return lhs<rhs;
  }
};
template<typename T>
class greater : public Compare<T>{
 public:
  virtual bool operator() (const T& lhs, const T& rhs) {
    return lhs>rhs;
  }
};
std::unique_ptr<Compare> GetComp(bool is_less) {
  if (is_less)
    return std::unique_ptr(new less) ;
  else
    return std::unique_ptr(new greater);
}*/
const Percent_t& GetMax(json &first, json &second, const std::string &key) {
  if(!first.count(key))
    return second[key];
  else if (!second.count(key))
    return first[key];
  return GetMax(first[key], second[key], (*CGlobalSingleton::getM_field_compare())[key]);
  /*if ((*CGlobalSingleton::getM_field_compare())[key])
    return std::max(first[key], second[key]);
  return std::max(first[key], second[key], std::greater<Percent_t >());*/
}
const Percent_t& GetMax(Percent_t &first, Percent_t &second, bool is_less) {
  if (is_less)
    return std::max(first, second);
  return std::max(first, second, std::greater<Percent_t >());
}
};
#endif //GAME_PROJ_CGLOBALSINGLETON_HPP

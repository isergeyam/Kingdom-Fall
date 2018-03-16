
// Created by sg on 15.03.18.
//

#ifndef GAME_PROJ_JSON_HPP
#define GAME_PROJ_JSON_HPP
#include <nlohmann/json.hpp>
using json = nlohmann::json;
/*namespace MyExtension{
void MyExtensionExtendJson(json &j1, const json &j2) {
  for (auto j = j2.begin();j != j2.end(); ++j) {
    j1[j.key()] = j.value();
  }
}
template<typename T>
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
}
const Percent_t& GetMax(json &first, json &second, const std::string &key) {
  if(!first.count(key))
    return second[key];
  else if (!second.count(key))
    return first[key];
  return GetMax(first[key], second[key], (*CGame::getM_field_compare())[key]);
  if ((*CGame::getM_field_compare())[key])
    return std::max(first[key], second[key]);
  return std::max(first[key], second[key], std::greater<Percent_t >());
}
const Percent_t& GetMax(Percent_t &first, Percent_t &second, bool is_less) {
  if (is_less)
    return std::max(first, second);
  return std::max(first, second, std::greater<Percent_t >());
}
};*/
#endif //GAME_PROJ_JSON_HPP

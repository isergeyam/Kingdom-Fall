//
// Created by sg on 22.04.18.
//
#include "../src/json-validator.hpp"
#include <iostream>
#include <fstream>
int main () {
  json_validator m_validator;
  std::string ability("json/schema/Ability.json"), data("json/DefaultUnit.json"), schema("json/schema/Unit.json");
  std::ifstream idata(data);
  std::ifstream iability(ability);
  std::ifstream ischema(schema);
  json m_schema = json::parse(ischema);
  m_schema["definitions"]["Ability"] = json::parse(iability);
  m_validator.set_root_schema(m_schema);
  m_validator.validate(json::parse(idata));
  return 0;
}


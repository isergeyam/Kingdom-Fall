//
// Created by sg on 18.04.18.
//

#pragma once
#include "json-validator.hpp"
#include <istream>
class CJsonValidatorAdapter {
 private:
  json_validator m_validator;
 public:
  void set_schema(const json &val);
  void validate(const json &obj_);
};



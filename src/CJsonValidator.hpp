//
// Created by sg on 18.04.18.
//

#pragma once
#include "json-validator.hpp"
#include <istream>
class CJsonValidator {
 private:
  json_validator m_validator;
 public:
  void set_schema(std::istream &stream_);
  void validate(const json& obj_);
};



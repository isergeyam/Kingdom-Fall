//
// Created by sg on 18.04.18.
//

#include "CJsonValidator.hpp"
void CJsonValidator::set_schema(std::istream &stream_) {
  m_validator.set_root_schema(json::parse(stream_));
}
void CJsonValidator::validate(const json &obj_) {
  m_validator.validate(obj_);
}

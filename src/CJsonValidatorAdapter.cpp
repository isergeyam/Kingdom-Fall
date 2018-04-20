//
// Created by sg on 18.04.18.
//

#include "CJsonValidatorAdapter.hpp"
void CJsonValidatorAdapter::set_schema(std::istream &stream_) {
  m_validator.set_root_schema(json::parse(stream_));
}
void CJsonValidatorAdapter::validate(const json &obj_) {
  m_validator.validate(obj_);
}

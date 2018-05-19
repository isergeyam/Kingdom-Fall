//
// Created by sg on 18.04.18.
//

#include "CJsonValidatorAdapter.hpp"
void CJsonValidatorAdapter::set_schema(const json &val) {
  m_validator.set_root_schema(val);
}
void CJsonValidatorAdapter::validate(const json &obj_) {
  m_validator.validate(obj_);
}

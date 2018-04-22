//
// Created by sg on 18.04.18.
//

#include "CJsonValidatorAdapter.hpp"
void CJsonValidatorAdapter::set_schema(json val) {
  m_validator.set_root_schema(std::move(val));
}
void CJsonValidatorAdapter::validate(json obj_) {
  m_validator.validate(std::move(obj_));
}

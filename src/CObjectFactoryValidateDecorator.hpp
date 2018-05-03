//
// Created by sg on 20.04.18.
//

#pragma once

#include <memory>
#include "IObjectFactory.hpp"
#include "CurrentSerializer.hpp"
template<typename _Object>
class CObjectFactoryValidateDecorator : public IObjectFactory<_Object> {
 private:
  std::shared_ptr<IObjectFactory<_Object>> my_factory;
 public:
  static CurrentValidator m_validator;
  explicit CObjectFactoryValidateDecorator(const std::shared_ptr<IObjectFactory<_Object>> &my_factory = nullptr);
  CObjectFactoryValidateDecorator &operator=(const CObjectFactoryValidateDecorator &other);
  std::shared_ptr<_Object> CreateObject(const CPosition &position) override;
  const CurrentSerializerType &getM_properties() const override;
};
template<typename _Object>
CObjectFactoryValidateDecorator<_Object>::CObjectFactoryValidateDecorator(const std::shared_ptr<IObjectFactory<_Object>> &my_factory)
    : my_factory(my_factory) {
  m_validator.validate(my_factory->getM_properties());
}
template<typename _Object>
std::shared_ptr<_Object> CObjectFactoryValidateDecorator<_Object>::CreateObject(const CPosition &position) {
  return my_factory->CreateObject(position);
}
template<typename _Object>
const CurrentSerializerType &CObjectFactoryValidateDecorator<_Object>::getM_properties() const {
  return my_factory->getM_properties();
}
template<typename _Object>
CObjectFactoryValidateDecorator<_Object> &CObjectFactoryValidateDecorator<_Object>::operator=(const CObjectFactoryValidateDecorator<
    _Object> &other) {
  my_factory = other.my_factory;
  return *this;
}
template<typename _Object>
CurrentValidator CObjectFactoryValidateDecorator<_Object>::m_validator;

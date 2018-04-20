//
// Created by sg on 20.04.18.
//

#include "CObjectFactoryValidateDecorator.hpp"
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

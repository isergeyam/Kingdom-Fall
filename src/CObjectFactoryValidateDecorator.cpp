//
// Created by sg on 10.05.18.
//
#include "CObjectFactoryValidateDecorator.hpp"
CObjectFactoryValidateDecorator::CObjectFactoryValidateDecorator(std::shared_ptr<IObjectFactory> my_copy_factory,
                                                                 std::unique_ptr<CurrentValidator> &&m_copy_validator)
    : my_factory(std::move(my_copy_factory)), m_validator(std::move(m_copy_validator)) {
  m_validator->validate(my_factory->getM_properties());
}
std::shared_ptr<CObject> CObjectFactoryValidateDecorator::CreateObject(const CPosition &position) {
  return my_factory->CreateObject(position);
}
const CurrentSerializerType &CObjectFactoryValidateDecorator::getM_properties() const {
  return my_factory->getM_properties();
}
CObjectFactoryValidateDecorator &CObjectFactoryValidateDecorator::operator=(const CObjectFactoryValidateDecorator &other) {
  my_factory = other.my_factory;
  return *this;
}


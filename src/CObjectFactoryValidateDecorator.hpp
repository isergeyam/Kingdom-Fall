//
// Created by sg on 20.04.18.
//

#pragma once

#include <memory>
#include "IObjectFactory.hpp"
#include "CurrentSerializer.hpp"
class CObjectFactoryValidateDecorator : public IObjectFactory {
 private:
  std::shared_ptr<IObjectFactory> my_factory;
  std::unique_ptr<CurrentValidator> m_validator;
 public:
  explicit CObjectFactoryValidateDecorator(std::shared_ptr<IObjectFactory> my_copy_factory,
                                             std::unique_ptr<CurrentValidator> &&m_copy_validator);
  CObjectFactoryValidateDecorator &operator=(const CObjectFactoryValidateDecorator &other);
  std::shared_ptr<CObject> CreateObject(const CPosition &position) override;
  const CurrentSerializerType &getM_properties() const override;
};

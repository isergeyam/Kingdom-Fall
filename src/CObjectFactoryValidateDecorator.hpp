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
  std::shared_ptr<CurrentValidator> m_validator;
 public:
  explicit CObjectFactoryValidateDecorator(const std::shared_ptr<IObjectFactory> &my_factory = nullptr);
  CObjectFactoryValidateDecorator &operator=(const CObjectFactoryValidateDecorator &other);
  std::shared_ptr<CObject> CreateObject(const CPosition &position) override;
  const CurrentSerializerType &getM_properties() const override;
};

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
  static CurrentValidator m_validator;
 public:
  explicit CObjectFactoryValidateDecorator(const std::shared_ptr<IObjectFactory<_Object>> &my_factory);
  std::shared_ptr<_Object> CreateObject(const CPosition &position) override;
  const CurrentSerializerType &getM_properties() const override;
};


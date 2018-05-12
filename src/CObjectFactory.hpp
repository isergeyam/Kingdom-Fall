//
// Created by sg on 18.04.18.
//

#pragma once
#include "CurrentSerializer.hpp"
#include "CPosition.hpp"
#include "IObjectFactory.hpp"
template<typename _Object>
class CObjectFactory : public IObjectFactory {
 protected:
  CurrentSerializerType m_properties;
 public:
  explicit CObjectFactory(CurrentSerializerType m_properties);
  const CurrentSerializerType &getM_properties() const override;
  std::shared_ptr<CObject> CreateObject(const CPosition &m_position) override;
  ~CObjectFactory() override = default ;
};

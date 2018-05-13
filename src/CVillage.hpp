//
// Created by sg on 18.04.18.
//

#pragma once
#include "CObject.hpp"
#include "CurrentSerializer.hpp"
class CVillage : public CObject {
 public:
  enum EState { VILLAGE_FREE, VILLAGE_OCCUPIED };
  CVillage(const CurrentSerializerType &m_properties, const CPosition &m_position);
  std::string GetInfo() override;
};



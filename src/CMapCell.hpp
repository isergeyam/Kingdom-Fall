//
// Created by sg on 18.04.18.
//

#pragma once
#include "CObject.hpp"
#include <memory>
#include <vector>
class CUnit;
class CVillage;
class CTerrain;
class CMapCell {
 private:
  std::shared_ptr<CUnit> m_unit;
  std::shared_ptr<CVillage> m_village;
  std::shared_ptr<CTerrain> m_terrain;
 public:
  CMapCell(const std::shared_ptr<CUnit> &m_unit,
           const std::shared_ptr<CVillage> &m_village,
           const std::shared_ptr<CTerrain> &m_terrain);
  const std::shared_ptr<CUnit> &getM_unit() const;
  const std::shared_ptr<CVillage> &getM_village() const;
  const std::shared_ptr<CTerrain> &getM_terrain() const;
  void setM_unit(const std::shared_ptr<CUnit> &m_unit);
  void setM_village(const std::shared_ptr<CVillage> &m_village);
  void setM_terrain(const std::shared_ptr<CTerrain> &m_terrain);
};



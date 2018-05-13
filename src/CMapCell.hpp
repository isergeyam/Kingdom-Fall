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
class CObjectController;
class CMapCell {
 private:
  std::shared_ptr<CObjectController> m_unit;
  std::shared_ptr<CObjectController> m_village;
  std::shared_ptr<CObjectController> m_terrain;
 public:
  CMapCell(const std::shared_ptr<CObjectController> &m_unit,
           const std::shared_ptr<CObjectController> &m_village,
           const std::shared_ptr<CObjectController> &m_terrain);
  explicit CMapCell(const std::shared_ptr<CObjectController> &m_terrain = nullptr);
  const std::shared_ptr<CUnit> &GetUnitObject() const;
  const std::shared_ptr<CVillage> &GetVillageObject() const;
  const std::shared_ptr<CTerrain> &GetTerrainObject() const;
  const std::shared_ptr<CObjectController> &getM_unit() const;
  const std::shared_ptr<CObjectController> &getM_village() const;
  const std::shared_ptr<CObjectController> &getM_terrain() const;
  const std::shared_ptr<CObjectController> &GetTopObject() const;
  void setM_unit(const std::shared_ptr<CObjectController> &m_unit);
  void setM_village(const std::shared_ptr<CObjectController> &m_village);
  void setM_terrain(const std::shared_ptr<CObjectController> &m_terrain);
};



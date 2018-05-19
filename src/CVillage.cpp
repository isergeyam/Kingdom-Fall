//
// Created by sg on 18.04.18.
//

#include "CVillage.hpp"
#include "CGlobalGame.hpp"
#include "CMap.hpp"
#include "CUnit.hpp"
CVillage::CVillage(const CurrentSerializerType &m_properties, const CPosition &m_position) : CObject(m_position,
                                                                                                     false,
                                                                                                     true,
                                                                                                     true,
                                                                                                     false,
                                                                                                     m_properties) {}
std::string CVillage::GetInfo() {
  return "Name: " + m_properties["Name"].get<std::string>();
}
void CVillage::ToggleAutoAbilities() {
  for (auto &&it : m_properties["AutoAbilities"]) {
    std::string cur_name = it["Name"].get<std::string>();
    if (cur_name == "Heal") {
      auto cur_unit = CGlobalGame::Instance()->CurMap()[m_position].GetUnitObject();
      if (cur_unit != nullptr) {
        cur_unit->setM_health(cur_unit->getM_health() + it["power"].get<Quantity_t >());
      }
    }
  }
}

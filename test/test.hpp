//
// Created by sg on 11.03.18.
//

#ifndef GAME_PROJ_TEST_HPP
#define GAME_PROJ_TEST_HPP
#include "../src/CUnitFactoryBuilder.hpp"
#include <fstream>
#include <gtest/gtest.h>
#include <iomanip>
class UnitsTest
    : public ::testing::TestWithParam<
          std::tuple<const char *, const char *, const char *, const char *>> {
};
TEST_P(UnitsTest, UnitsTest_UnitsBuilding_Test) {
  std::ifstream iDefaultUnit(std::get<0>(GetParam()));
  std::ifstream iUnitRace(std::get<1>(GetParam()));
  std::ifstream iUnitType(std::get<2>(GetParam()));
  std::ifstream iExpectedUnit(std::get<3>(GetParam()));
  std::ifstream iValidateUnit("json/schema/Unit.json");
  std::ifstream iValidateType("json/schema/Type.json");
  std::ifstream iValidateRace("json/schema/Race.json");
  // TODO
//  CUnitFactoryBuilder::m_default_validator.set_schema(iValidateUnit);
//  CUnitFactoryBuilder::m_type_validator.set_schema(iValidateType);
//  CUnitFactoryBuilder::m_race_validator.set_schema(iValidateRace);
  CUnitFactoryBuilder Builder;
  Builder.setM_default(CurrentSerializer::Deserialize(iDefaultUnit));
  Builder.setM_race(CurrentSerializer::Deserialize(iUnitRace));
  Builder.setM_type(CurrentSerializer::Deserialize(iUnitType));
  EXPECT_EQ(Builder.GetFactory()->getM_properties(), CurrentSerializer::Deserialize(iExpectedUnit));
  iDefaultUnit.close();
  iUnitType.close();
  iUnitRace.close();
  iExpectedUnit.close();
  iValidateUnit.close();
}
INSTANTIATE_TEST_CASE_P(INST_HUMAN_SWORDSMAN, UnitsTest,
                        ::testing::Values(std::make_tuple(
                            "json/DefaultUnit.json", "json/HumanRace.json",
                            "json/SwordsmanType.json",
                            "json/UnitHumanSwordsman.json")));
INSTANTIATE_TEST_CASE_P(INST_DWARF_SWORDSMAN, UnitsTest,
                        ::testing::Values(std::make_tuple(
                            "json/DefaultUnit.json", "json/DwarfRace.json",
                            "json/SwordsmanType.json",
                            "json/UnitDwarfSwordsman.json")));
#endif // GAME_PROJ_TEST_HPP

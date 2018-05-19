//
// Created by sg on 11.03.18.
//

#ifndef GAME_PROJ_TEST_HPP
#define GAME_PROJ_TEST_HPP
#include "../src/CUnitFactoryBuilder.hpp"
#include "../src/CGlobalGame.hpp"
#include "../src/CMap.hpp"
#include <fstream>
#include <gtest/gtest.h>
#include <iomanip>
class UnitBuildingTest
    : public ::testing::TestWithParam<
        std::tuple<const char *, const char *, const char *, const char *>> {
};
TEST_P(UnitBuildingTest, UnitsTest_UnitsBuilding_Test) {
  std::ifstream iValidateRace("json/schema/Race.json");
  std::ifstream iValidateType("json/schema/Type.json");
  std::ifstream iDefaultUnit(std::get<0>(GetParam()));
  std::ifstream iUnitRace(std::get<1>(GetParam()));
  std::ifstream iUnitType(std::get<2>(GetParam()));
  std::ifstream iExpectedUnit(std::get<3>(GetParam()));
  CurrentValidator m_val1, m_val2;
  m_val1.set_schema(CurrentSerializer::Deserialize(iValidateRace));
  m_val2.set_schema(CurrentSerializer::Deserialize(iValidateType));
  CUnitFactoryBuilder::m_race_validator = std::move(m_val1);
  CUnitFactoryBuilder::m_type_validator = std::move(m_val2);
  CUnitFactoryBuilder Builder;
  Builder.setM_default(std::make_unique<CurrentSerializerType>(CurrentSerializer::Deserialize(iDefaultUnit)));
  Builder.setM_race(CurrentSerializer::Deserialize(iUnitRace));
  Builder.setM_type(CurrentSerializer::Deserialize(iUnitType));
  EXPECT_TRUE(Builder.GetFactory()->getM_properties() == CurrentSerializer::Deserialize(iExpectedUnit));
}
class UnitMovementTest : public ::testing::TestWithParam<std::tuple<const char *,
                                                                    const char *,
                                                                    CPosition,
                                                                    CPosition,
                                                                    Quantity_t> > {
};
TEST_P(UnitMovementTest, UnitMovementTest_Units_Test) {
  std::ifstream m_settings(std::get<0>(GetParam()));
  CGlobalGame::Instance()->GlobalSetUp(m_settings);
  std::ifstream iUnit(std::get<1>(GetParam()));
  CPosition start_pos = std::get<2>(GetParam());
  CPosition end_pos = std::get<3>(GetParam());
  Quantity_t expected_ans = std::get<4>(GetParam());
  auto cur_val = std::make_unique<CurrentValidator >(*CGlobalGame::Instance()->getM_validate_unit());
  CObjectFactoryValidateDecorator
      m_factory(std::make_shared<CUnitFactory>(CurrentSerializer::Deserialize(iUnit)), std::move(cur_val));
  auto m_unit = std::dynamic_pointer_cast<CUnit>(m_factory.CreateObject(start_pos));
  EXPECT_TRUE(expected_ans==m_unit->CalculateDistance(end_pos));
}
INSTANTIATE_TEST_CASE_P(INST_HUMAN_SWORDSMAN, UnitBuildingTest,
                        ::testing::Values(std::make_tuple(
                            "json/DefaultUnit.json", "json/HumanRace.json",
                            "json/SwordsmanType.json",
                            "json/UnitHumanSwordsman.json")));
INSTANTIATE_TEST_CASE_P(INST_DWARF_SWORDSMAN, UnitBuildingTest,
                        ::testing::Values(std::make_tuple(
                            "json/DefaultUnit.json", "json/DwarfRace.json",
                            "json/SwordsmanType.json",
                            "json/UnitDwarfSwordsman.json")));
INSTANTIATE_TEST_CASE_P(INST_HUMAN_GRASS,
                        UnitMovementTest,
                        ::testing::Values(std::make_tuple("test/test_settings1.json",
                                                          "json/UnitHumanSwordsman.json",
                                                          CPosition(0, 0),
                                                          CPosition(2, 2),
                                                          static_cast<Quantity_t >(44))));
INSTANTIATE_TEST_CASE_P(INST_DWARF_GRASS,
                        UnitMovementTest,
                        ::testing::Values(std::make_tuple("test/test_settings1.json",
                                                          "json/UnitDwarfSwordsman.json",
                                                          CPosition(0, 0),
                                                          CPosition(2, 2),
                                                          static_cast<Quantity_t >(54))));
INSTANTIATE_TEST_CASE_P(INST_DWARF_MIXED,
                        UnitMovementTest,
                        ::testing::Values(std::make_tuple("test/test_settings2.json",
                                                          "json/UnitDwarfSwordsman.json",
                                                          CPosition(0, 0),
                                                          CPosition(4, 3),
                                                          static_cast<Quantity_t>(122))));
INSTANTIATE_TEST_CASE_P(INST_HUMAN_MIXED,
                        UnitMovementTest,
                        ::testing::Values(std::make_tuple("test/test_settings2.json",
                                                          "json/UnitHumanSwordsman.json",
                                                          CPosition(0, 0),
                                                          CPosition(4, 3),
                                                          static_cast<Quantity_t>(126))));
INSTANTIATE_TEST_CASE_P(INST_NOT_ACCESSIBLE,
                        UnitMovementTest,
                        ::testing::Values(std::make_tuple("test/test_settings3.json",
                                                          "json/UnitHumanSwordsman.json",
                                                          CPosition(0, 0),
                                                          CPosition(2, 2),
                                                          CGlobalGame::MaxDistance)));
#endif // GAME_PROJ_TEST_HPP

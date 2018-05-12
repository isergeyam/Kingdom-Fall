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
class MyEnvironment : public ::testing::Environment {
 public:
  void SetUp() override {
    CGlobalGame::GlobalSetUp();
  }
};
TEST(GlobalGameTest, InitializerTest) {
    
}
/*class UnitBuildingTest
    : public ::testing::TestWithParam<
        std::tuple<const char *, const char *, const char *, const char *>> {
};
TEST_P(UnitBuildingTest, UnitsTest_UnitsBuilding_Test) {
  std::ifstream iDefaultUnit(std::get<0>(GetParam()));
  std::ifstream iUnitRace(std::get<1>(GetParam()));
  std::ifstream iUnitType(std::get<2>(GetParam()));
  std::ifstream iExpectedUnit(std::get<3>(GetParam()));
  CUnitFactoryBuilder Builder;
  Builder.setM_default(CurrentSerializer::Deserialize(iDefaultUnit));
  Builder.setM_race(CurrentSerializer::Deserialize(iUnitRace));
  Builder.setM_type(CurrentSerializer::Deserialize(iUnitType));
  EXPECT_EQ(Builder.GetFactory()->getM_properties(), CurrentSerializer::Deserialize(iExpectedUnit));
}
class UnitMovementTest : public ::testing::TestWithParam<std::tuple<const char *,
                                                                    const char *,
                                                                    CPosition,
                                                                    CPosition,
                                                                    Quantity_t> > {
};
TEST_P(UnitMovementTest, UnitMovementTest_Units_Test) {
  std::ifstream iMap(std::get<0>(GetParam()));
  std::ifstream iUnit(std::get<1>(GetParam()));
  std::ifstream iGrass("json/GrassTerrain.json");
  std::ifstream iRock("json/RockTerrain.json");
  std::ifstream iHighRock("json/HighRockTerrain.json");
  std::ifstream iDungeon("json/DungeonTerrain.json");
  CPosition start_pos = std::get<2>(GetParam());
  CPosition end_pos = std::get<3>(GetParam());
  Quantity_t expected_ans = std::get<4>(GetParam());
  CGlobalGame::InitializeObjects(std::vector<CurrentSerializerType>{CurrentSerializer::Deserialize(iGrass),
                                                                    CurrentSerializer::Deserialize(iRock),
                                                                    CurrentSerializer::Deserialize(iHighRock),
                                                                    CurrentSerializer::Deserialize(iDungeon)});
  CGlobalGame::Map() = std::make_shared<CMap>(iMap);
  CObjectFactoryValidateDecorator<CUnit>
      m_factory(std::make_shared<CUnitFactory>(CurrentSerializer::Deserialize(iUnit)));
  auto m_unit = m_factory.CreateObject(start_pos);
  EXPECT_EQ(expected_ans, m_unit->CalculateDistance(end_pos));
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
                        ::testing::Values(std::make_tuple("maps/map1.txt",
                                                          "json/UnitHumanSwordsman.json",
                                                          CPosition(0, 0),
                                                          CPosition(2, 2),
                                                          static_cast<Quantity_t >(20))));
INSTANTIATE_TEST_CASE_P(INST_DWARF_GRASS,
                        UnitMovementTest,
                        ::testing::Values(std::make_tuple("maps/map1.txt",
                                                          "json/UnitDwarfSwordsman.json",
                                                          CPosition(0, 0),
                                                          CPosition(2, 2),
                                                          static_cast<Quantity_t >(24))));
INSTANTIATE_TEST_CASE_P(INST_DWARF_MIXED,
                        UnitMovementTest,
                        ::testing::Values(std::make_tuple("maps/map2.txt",
                                                          "json/UnitDwarfSwordsman.json",
                                                          CPosition(0, 0),
                                                          CPosition(4, 3),
                                                          static_cast<Quantity_t>(54))));
INSTANTIATE_TEST_CASE_P(INST_HUMAN_MIXED,
                        UnitMovementTest,
                        ::testing::Values(std::make_tuple("maps/map2.txt",
                                                          "json/UnitHumanSwordsman.json",
                                                          CPosition(0, 0),
                                                          CPosition(4, 3),
                                                          static_cast<Quantity_t>(56))));
INSTANTIATE_TEST_CASE_P(INST_NOT_ACCESSIBLE,
                        UnitMovementTest,
                        ::testing::Values(std::make_tuple("maps/map3.txt",
                                                          "json/UnitHumanSwordsman.json",
                                                          CPosition(0, 0),
                                                          CPosition(2, 2),
                                                          CGlobalGame::MaxDistance)));
                                                          */
#endif // GAME_PROJ_TEST_HPP

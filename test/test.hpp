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
    : public ::testing::TestWithParam<std::pair<const char *, const char *>> {};
TEST_P(UnitsTest, UnitsTest_UnitsBuilding_Test) {
  std::ifstream ifs(GetParam().first);
  json Game = json::parse(ifs);
  ifs.close();
  CUnitFactoryBuilder Builder;
  Builder.setM_default(Game["DefaultUnit"]);
  Builder.setM_race(Game["Races"][1]);
  Builder.setM_type(Game["Types"][0]);
  std::ofstream ofs(GetParam().second);
  ofs << std::setprecision(2) << Builder.GetFactory()->getM_unit().dump(2);
}
INSTANTIATE_TEST_CASE_P(INST_DEFAULT, UnitsTest,
                        ::testing::Values(std::make_pair(
                            "json/GameOptions.json", "GenUnitHuman.json")));
#endif // GAME_PROJ_TEST_HPP

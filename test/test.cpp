//
// Created by sg on 16.03.18.
//
#define KINGDOM_FALL_WITH_GRAPHICS 1
#include "test.hpp"
int main (int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  ::testing::AddGlobalTestEnvironment(new MyEnvironment);
  return RUN_ALL_TESTS();
}

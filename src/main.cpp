//
// Created by sg on 14.05.18.
//
#define KINGDOM_FALL_WITH_GRAPHICS 1
#include "CGlobalGame.hpp"
int main () {
  SDL2pp::SDLTTF ttf;
  std::ifstream ifs("settings.json");
  CGlobalGame::GlobalSetUp(ifs);
  CGlobalGame::StartGame();
  return 0;
}

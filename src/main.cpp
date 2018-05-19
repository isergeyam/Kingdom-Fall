//
// Created by sg on 14.05.18.
//
#include "CGlobalGame.hpp"
int main () {
  SDL2pp::SDLTTF ttf;
  std::ifstream ifs("settings.json");
  CGlobalGame::Instance()->GlobalSetUp(ifs);
  CGlobalGame::Instance()->StartGame();
  return 0;
}

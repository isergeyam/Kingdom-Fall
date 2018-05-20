//
// Created by sg on 14.05.18.
//
#include "CGlobalGame.hpp"
int main () {
  SDL2pp::SDL sdl(SDL_INIT_VIDEO);
  SDL2pp::SDLTTF sdl_ttf;
  std::ifstream ifs("settings.json");
  CGlobalGame::Instance()->GlobalSetUp(ifs);
  CGlobalGame::Instance()->StartGame();
  return 0;
}

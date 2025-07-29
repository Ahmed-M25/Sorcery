#include "core/Game.h"
#include <iostream>

int main(int argc, char** argv) {
  try {
    Game game(argc, argv);
    game.startGame();
  }
  catch (const std::exception& e) {
    std::cerr << "Error; " << e.what() << std::endl;
    return 1;
  }

  return 0;
}

#include <iostream>
#include "ludo.h"

void prompt(Color, int);

int main() {
  
  Ludo game;
  Color currentPlayer = RED;
  
  while (!game.won()) {
    game.display();
    int roll = game.roll(), fieldToMove;
    prompt(currentPlayer, roll);
    std::cin >> fieldToMove;
    while (game.move(currentPlayer, fieldToMove, roll)) {
      game.display();
      roll = game.roll();
      prompt(currentPlayer, roll);
      std::cin >> fieldToMove;
    }
    currentPlayer = (Color)((currentPlayer + 1) % NUM_PLAYERS);
  }
  return 0;
}

void prompt(Color currentPlayer, int roll) {
  std::cout << Ludo::colorToString(currentPlayer) << " rolled " << roll << std::endl << "What piece do you want to move? (0-3): ";
}
#include <iostream>
#include "ludo.h"

void prompt(Color, int);

int selectPiece() {
  int input;
  while (true) {
    std::cin >> input;
    if(input >= 0 && input < NUM_PIECES) {
      return input;
    }
  }
}

int main() {
  
  Ludo game;
  Color currentPlayer = RED;
  int roll = game.roll();
  while (!game.won()) {
    game.display();
    roll = game.roll();
    prompt(currentPlayer, roll);
    int selectedPiece = selectPiece();
    while (game.move(currentPlayer, selectedPiece, roll)) {
      game.display();
      roll = game.roll();
      prompt(currentPlayer, roll);
      selectedPiece = selectPiece();
    }
    currentPlayer = (Color)((currentPlayer + 1) % NUM_PLAYERS);
  }
  return 0;
}

void prompt(Color currentPlayer, int roll) {
  std::cout << Ludo::colorToString(currentPlayer) << " rolled " << roll << std::endl << "What piece do you want to move? (0-3): ";
}
#include <iostream>
#include "catch-and-run.h"

void prompt(Color, int);

int selectPiece() {
  int input;
  while (true) {
    std::cin >> input;
    if(input >= 1 && input <= NUM_PIECES) {
      return input - 1;
    }
  }
}

int main() {
  
  CatchAndRun game;
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
  std::cout << CatchAndRun::colorToString(currentPlayer) << " rolled " << roll << std::endl << "What piece do you want to move? (1-3): ";
}
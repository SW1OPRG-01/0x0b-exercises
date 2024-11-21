#include "catch-and-run.h"

#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <string>

// returns the field for a given player's piece
int CatchAndRun::getField(Color player, int piece) {
  return players[player][piece].position;
}

bool CatchAndRun::extraRoll(int rolled) {
  return rolled == 6;
}

bool CatchAndRun::isFieldFree(int field) {
  return board[field] == NULL;
}

bool CatchAndRun::isPieceAtStart(Color player, int piece) {
  return (getField(player, piece) == 0);
}

bool CatchAndRun::isSamePlayer(Color player, int newField) {
  return (board[newField]->color == player);
}

std::string CatchAndRun::colorToString(Color c) {
  switch (c) {
  case RED:
    return "R";
  case YELLOW:
    return "Y";
  case GREEN:
    return "G";
  case BLUE:
    return "B";
  }
  return "NA";
}

CatchAndRun::CatchAndRun() {
  // Der er ingen brikker på spillepladen (alle er på position 0)
  for (int i = 0; i < BOARD_SIZE; i++) {
    board[i] = NULL;
  }
  // opret spillernes brikker (og placer dem hjemme)
  for (int player = 0; player < NUM_PLAYERS; player++) {
    for (int piece = 0; piece < NUM_PIECES; piece++) {
      players[player][piece].color = (Color)player;
      players[player][piece].position = 0;
      players[player][piece].id = piece + 1;
    }
  }
  // initialiser random generatoren
  srand(time(NULL));
}

// Metode til at flytte en brik. Returnerer om der er ekstra slag
bool CatchAndRun::move(Color player, int pieceNo, int rolled) {
  int newField = getField(player, pieceNo) + rolled;
  std::cout << "NEW FIELD: " << newField << std::endl;
  bool extra = extraRoll(rolled);

  if (newField >= BOARD_SIZE) {
    return false; // brik udenfor spillepladen, gør intet
  }

  if (newField == BOARD_SIZE - 1) {                                               // brik er kommet hjem
    board[getField(player, pieceNo)] = NULL;      // fjern brikken fra det tidligere felt
    players[player][pieceNo].position = newField; // opdater positionen hos spilleren
    return extra;
  }

  if (isFieldFree(newField)) {
    // felt ledigt, flyt brik herhen
    if (isPieceAtStart(player, pieceNo)) {
      board[newField] = &players[player][pieceNo]; // opdater til at pege på spillers brik
    } else {
      board[newField] = board[getField(player, pieceNo)]; // sæt ny position til at pege på brikken
      board[getField(player, pieceNo)] = NULL;            // fjern brikken fra det tidligere felt
    }
    players[player][pieceNo].position = newField; // opdater positionen hos spilleren
  } else { // der står noget på pladsen
    if (!isSamePlayer(player, newField)) {                                // slå anden spillers brik hjem
      board[newField]->position = 0; // flyt anden spillers brik hjem
      if (isPieceAtStart(player, pieceNo)) {
        board[newField] = &players[player][pieceNo]; // opdater til at pege på spillers brik
      } else {
        board[newField] = board[getField(player, pieceNo)]; // sæt ny position til at pege på brikken
        board[getField(player, pieceNo)] = NULL;            // fjern brikken fra det tidligere felt
      }
      players[player][pieceNo].position = newField; // opdater positionen hos spilleren
    }
  }
  return extra;
}

bool CatchAndRun::won() {
  bool winner = false;
  for (int p = RED; p <= BLUE; p++) {
    int noHome = 0;
    for (int i = 0; i < NUM_PIECES; i++) {
      if (players[p][i].position == BOARD_SIZE) {
        noHome++;
      }
    }

    if (noHome == NUM_PIECES) {
      winner = true;
    }
  }
  return winner;
}

int CatchAndRun::roll() {
  return (rand() % 6) + 1;
}

// udskriver spillepladen
void CatchAndRun::display() {
  // Udskriv dem som er på start
  std::cout << std::endl << "Pieces @ start\t";
  for (int p = RED; p <= BLUE; p++) {
    for (int i = 0; i < NUM_PIECES; i++) {
      if (players[p][i].position == 0) {
        std::cout << colorToString(players[p][i].color) << players[p][i].id << ",";
      }
    }
  }
  std::cout << std::endl;
  std::cout << "Pieces @ home\t";
  for (int p = RED; p <= BLUE; p++) {
    for (int i = 0; i < NUM_PIECES; i++) {
      if (players[p][i].position == BOARD_SIZE - 1)
      {
        std::cout << colorToString(players[p][i].color) << players[p][i].id << "|";
      }
    }
  }
  std::cout << std::endl << std::endl;
  std::cout << "Board state\t";
  for (int i = 1; i < BOARD_SIZE; i++) {
    std::cout << "|";
    if (board[i] == NULL) {
      std::cout << "  ";
    } else {
      std::cout << colorToString(board[i]->color) << board[i]->id;
    }
  }
  std::cout << std::endl << std::endl;
}
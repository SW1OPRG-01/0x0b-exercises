#include "catch_and_run.h"

#include <iostream>
#include <vector>
#include <cstdlib> // for rand() og srand()
#include <ctime>   // for time()
#include <string>

// returns the field of the given player's piece
int Ludo::getField(Color player, int piece) {
  return players[player][piece].position;
}

// returns if the roll allows for an extra roll
bool Ludo::extraRoll(int rolled) {
  return rolled == 6;
}

// returns if the field is empty
bool Ludo::fieldFree(int field) {
  return board[field] == NULL;
}

// returns if the field is at start position
bool Ludo::start(Color player, int piece) {
  return (getField(player, piece) == 0);
}

// returns if player is at newField
bool Ludo::samePlayer(Color player, int newField) {
  return (board[newField]->color == player);
}

// returns if the field if a field where a random opponent's piece if sent home
bool Ludo::sendHome(int field) {
  return (field % 10 == 0);
}

// sends a random other players piece to home
void Ludo::sendRandomToHome(Color player) {
  int otherPlayer = rand() % 4;
  while (otherPlayer == player) {
    otherPlayer = rand() % 4;
  }
  // nu er der en anden tilfældig spiller valgt
  int p = rand() % 4; // tilfældig brik
  if (!start((Color)otherPlayer, p)) { // brikken ikke på start
    Piece *other = board[getField((Color)otherPlayer, p)];
    board[getField((Color)otherPlayer, p)] = NULL;
    other->position = 0;
  }
}

std::string Ludo::colorToString(Color c) {
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

Ludo::Ludo() {
  // Der er ingen brikker på spillepladen (alle er på position 0)
  for (int i = 0; i < BOARD_SIZE; i++) {
    board[i] = NULL;
  }
  // opret spillernes brikker (og placer dem hjemme)
  for (int player = 0; player < NUM_PLAYERS; player++) {
    for (int piece = 0; piece < NUM_PIECES; piece++) {
      players[player][piece].color = (Color)player;
      players[player][piece].position = 0;
      players[player][piece].id = piece;
    }
  }
  // initialiser random generatoren
  srand(time(NULL));
}

// Metode til at flytte en brik. Returnerer om der er ekstra slag
bool Ludo::move(Color player, int pieceNo, int rolled) {
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

  if (fieldFree(newField)) {
    if (sendHome(player)) {
      sendRandomToHome(player);
    }
    // felt ledigt, flyt brik herhen
    if (start(player, pieceNo)) {
      board[newField] = &players[player][pieceNo]; // opdater til at pege på spillers brik
    } else {
      board[newField] = board[getField(player, pieceNo)]; // sæt ny position til at pege på brikken
      board[getField(player, pieceNo)] = NULL;            // fjern brikken fra det tidligere felt
    }
    players[player][pieceNo].position = newField; // opdater positionen hos spilleren
  } else { // der står noget på pladsen
    if (!samePlayer(player, newField)) {                                // slå anden spillers brik hjem
      board[newField]->position = 0; // flyt anden spillers brik hjem
      if (start(player, pieceNo)) {
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

// er der en spiller som har vundet
bool Ludo::won() {
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

int Ludo::roll() {
  return (rand() % 6) + 1;
}

// udskriver spillepladen
void Ludo::display() {
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
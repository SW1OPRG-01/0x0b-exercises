#include <string>

static const int BOARD_SIZE = 24;
static const int NUM_PIECES = 3;
static const int NUM_PLAYERS = 4;

enum Color { RED, YELLOW, GREEN, BLUE };

struct Piece {
  Color color;
  int position;
  int id;
};


class Ludo {
  public:
    Ludo();
    bool move(Color player, int id, int rolled);
    bool won();
    int roll();
    void display();
    static std::string colorToString(Color color);
  private:
    Piece* board[BOARD_SIZE];
    Piece players[NUM_PLAYERS][NUM_PIECES];
    int getField(Color player, int piece);
    bool extraRoll(int rolled);
    bool fieldFree(int f);
    bool start(Color player, int piece);
    bool samePlayer(Color player, int nextField);
    bool sendHome(int field);
    void sendRandomToHome(Color player);
};
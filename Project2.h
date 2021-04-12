#include <string>
#include <iostream>
#include <vector>
#include <tuple>
#include <time.h>

#define ROWS 6
#define COLUMNS 7

struct Node
{
  int value, row, col;
  std::vector<Node> path;

  Node(int v, std::vector<Node> p)
  {
    value = v;
    path = p;
  }

  Node(int v, int r, int c, std::vector<Node> p)
  {
    value = v;
    row = r;
    col = c;
    path = p;
  }
};

class Connect4
{
public:
  // function declarations:
  Connect4();
  Node minimaxAB(int depth, bool player, int useThresh, int passThresh);
  bool deepEnough(int depth);
  std::vector<Node> moveGen(bool player);
  void drawBoard();
  void playGame();
  void updateBoard(Node move);
  char getPiece(int slot);

  //TODO: for each group member, define evaluation functions (print tables to a file?)
  int staticEval(bool player);

private:
  int board[ROWS][COLUMNS];
};

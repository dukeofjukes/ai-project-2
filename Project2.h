#include <string>
#include <iostream>
#include <vector>
#include <tuple>
#include <time.h>

#define ROWS 6
#define COLUMNS 7

struct Node
{
  int value;                                //The evaluation value of this state
  std::vector<std::vector<int>> state;      //The game board that would represent this state
  std::vector<Node> path;                   //The path that led to this state

  Node(std::vector<std::vector<int>> state) //State initializer
  {
    this->state = state;
  }
};

class Connect4
{
public:
  // function declarations:
  Connect4();
  Node minimaxAB(Node position, int depth, bool player, int useThresh, int passThresh);
  bool deepEnough(int depth);
  std::vector<Node> moveGen(bool player, Node position);
  void drawBoard();
  void playGame();
  void updateBoard(Node move);
  char getPiece(int slot);

  //TODO: for each group member, define evaluation functions (print tables to a file?)
  int staticEval(bool player, Node position);

private:
  std::vector<std::vector<int>> board;
  int i;
};

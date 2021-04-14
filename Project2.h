#include <string>
#include <iostream>
#include <vector>
#include <tuple>
#include <time.h>
using namespace std;

#define ROWS 6
#define COLUMNS 7

// FIXME: this might be necessary to differentiate between game over states
enum Winner
{
  max,
  min,
  draw,
  none
};

struct Node
{
  int value;                                //The evaluation value of this state
  vector<vector<int>> state;      //The game board that would represent this state
  vector<Node> path;                   //The path that led to this state

  Node(vector<vector<int>> state) //State initializer
  {
    this->state = state;
  }
};

class Connect4
{
public:
  const bool MAX = true;
  const bool MIN = false;
  // function declarations:
  Connect4();
  void playGame();
  void updateBoard(Node move);
  Node minimaxAB(Node position, int depth, bool player, int useThresh, int passThresh);
  bool deepEnough(Node position, int depth, bool player);
  int staticEval(bool player, Node position); //TODO: for each group member, define evaluation functions (print tables to a file?)
  vector<Node> moveGen(bool player, Node position);
  Winner winningMove(Node position, bool player); // TODO: checks if position.state is a win state, gets called in playGame after every turn
  void drawBoard(vector<vector<int>>);
  char getPiece(int slot);

private:
  vector<vector<int>> board;
  int i;
};

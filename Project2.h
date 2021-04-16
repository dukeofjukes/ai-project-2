#include <string>
#include <iostream>
#include <vector>
#include <tuple>
#include <time.h>
using namespace std;

#define ROWS 6
#define COLUMNS 7

// an enumerator intended for use in checking the win state of a board:
// FIXME: consider just reverting to an int to represent this
enum WinState
{
  max,
  min,
  none
};

//  
struct Node
{
  vector<vector<int>> state; // the game board that would represent this state
  int value; // the static evaluation value of this state
  vector<Node> path; // the path of child nodes that follows this state

  Node(vector<vector<int>> state) // state initializer
  {
    this->state = state;
  }
};

class Connect4
{
public:
  // FIXME: might be unnecessary, but wait to delete until we start implementing different games and evals.
  const bool MAX = true;
  const bool MIN = false;
  
  // function declarations:
  Connect4();
  void playGame();
  Node minimaxAB(Node position, int depth, bool player, int useThresh, int passThresh);
  bool deepEnough(Node position, int depth);
  // FIXME: once we start implementing more evals and different games, should we print to a file?
  int staticEval(bool player, Node position);
  // TODO: define more staticEvals with different names (maybe have the names be descriptive as to what they actually do)
  vector<Node> moveGen(bool player, Node position);
  WinState winningMove(Node position, bool player);
  void drawBoard(vector<vector<int>>);
  char getPiece(int slot);

private:
  vector<vector<int>> board;
  int evaluationTable[ROWS][COLUMNS] = {{3, 4, 5, 7, 5, 4, 3},
                                        {4, 6, 8, 10, 8, 6, 4},
                                        {5, 8, 11, 13, 11, 8, 5}, 
                                        {5, 8, 11, 13, 11, 8, 5},
                                        {4, 6, 8, 10, 8, 6, 4},
                                        {3, 4, 5, 7, 5, 4, 3}};
};

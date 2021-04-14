#include <string>
#include <iostream>
#include <vector>
#include <tuple>
#include <time.h>
using namespace std;

#define ROWS 6
#define COLUMNS 7

// FIXME: this might be necessary to differentiate between game-over states
enum WinState
{
  max,
  min,
  draw,
  none
};

struct Node
{
  int value; // the static evaluation value of this state
  vector<vector<int>> state; // the game board that would represent this state
  vector<Node> path; // the path of child nodes that follows this state

  Node(vector<vector<int>> state) // state initializer
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
  // TODO: for each group member, define evaluation functions (print tables to a file?)
  int staticEval(bool player, Node position);
  vector<Node> moveGen(bool player, Node position);
  WinState winningMove(Node position, bool player); // TODO: checks if position.state is a win state, gets called in playGame after every turn
  void drawBoard(vector<vector<int>>);
  char getPiece(int slot);

private:
  vector<vector<int>> board;
  int i; // FIXME: remove after done with debugging, or rename as a way to track efficiency
  int evaluationTable[ROWS][COLUMNS] = {{3, 4, 5, 7, 5, 4, 3},
                                        {4, 6, 8, 10, 8, 6, 4},
                                        {5, 8, 11, 13, 11, 8, 5}, 
                                        {5, 8, 11, 13, 11, 8, 5},
                                        {4, 6, 8, 10, 8, 6, 4},
                                        {3, 4, 5, 7, 5, 4, 3}};
};

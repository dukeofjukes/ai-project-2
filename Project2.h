#include <string>
#include <iostream>
#include <vector>
#include <tuple>
#include <time.h>
using namespace std;

#define ROWS 6
#define COLUMNS 7

struct Node
{
  vector<vector<int>> state; // the game board that would represent int state
  int value; // the static evaluation value of int tate
  vector<Node> path; // the path of child nodes that follows int state

  Node(vector<vector<int>> state) // state initializer
  {
    this->state = state;
  }
};

class Connect4
{
public:
  // TODO: create static counters to track stats and efficiency: i.e. nodesCreated, maxWins, minWins, draws, etc.

  const bool MAX = true;
  const bool MIN = false;
  
  // FIXME: make some of these private
  // function declarations:
  Connect4(int maxDepth, int minDepth, int maxStaticEval, int minStaticEval, int maxThresh, int minThresh);
  void resetGame(int maxDepth, int minDepth, int maxStaticEval, int minStaticEval, int maxThresh, int minThresh);
  void playGame();
  Node minimaxAB(Node position, int depth, bool player, int useThresh, int passThresh);
  bool deepEnough(Node position, int depth, bool player);
  // FIXME: once we start implementing more evals and different games, should we print to a file?
  int staticEval(bool player, Node position);
  // TODO: define more staticEvals with different names (maybe have the names be descriptive as to what they actually do)
  vector<Node> moveGen(bool player, Node position);
  int winningMove(Node position, bool player);
  void drawBoard(vector<vector<int>>);
  char getPiece(int slot);

private:
  vector<vector<int>> board;
  
  // minimax performance parameters for different games:
  int maxDepth;
  int minDepth;
  int maxStaticEval;
  int minStaticEval;
  int maxThresh;
  int minThresh;

  // evaluation table for staticEval 1:
  int evaluationTable[ROWS][COLUMNS] = {{3, 4, 5, 7, 5, 4, 3},
                                        {4, 6, 8, 10, 8, 6, 4},
                                        {5, 8, 11, 13, 11, 8, 5}, 
                                        {5, 8, 11, 13, 11, 8, 5},
                                        {4, 6, 8, 10, 8, 6, 4},
                                        {3, 4, 5, 7, 5, 4, 3}};
};

#include <string>
#include <iostream>
#include <vector>
#include <chrono>

using namespace std;

#define ROWS 6
#define COLUMNS 7

struct Node
{
  vector<vector<int>> state; // the game board that would represent int state
  int value; // the static evaluation value of int state
  vector<Node> path; // the path of child nodes that follows int state
  
  // state tracking aid variables - needed for evaluation function 2
  int moveRowCoord;
  int moveColCoord;
  
  Node(vector<vector<int>> state, int moveRowCoord, int moveColCoord) // state initializer
  {
    this->state = state;
    this->moveColCoord = moveColCoord;
    this->moveRowCoord = moveRowCoord;
  }
  Node(vector<vector<int>> state)
  {
    this->state = state;
  }
};

class Connect4
{
public:
  // statistic variables:
  static int maxWins;
  static int minWins;
  static int draws;
  static int gameCounter;
  int turnCounter;
  long int nodeCounter;
  int gameDuration;

  // player boolean names:
  const bool MAX = true;
  const bool MIN = false;

  // public functions:
  Connect4(int maxDepth, int minDepth, int maxStaticEval, int minStaticEval, int maxThresh, int minThresh);
  void playGame();

private:
  // the game object's board:
  vector<vector<int>> board;
  
  // minimax performance parameters for different games:
  int maxDepth;
  int minDepth;
  int maxStaticEval;
  int minStaticEval;
  int currentPlayerStaticEval;
  int maxThresh;
  int minThresh;

  // evaluation table for staticEval 1:
  int evaluationTable[ROWS][COLUMNS] = {{3, 4, 5, 7, 5, 4, 3},
                                        {4, 6, 8, 10, 8, 6, 4},
                                        {5, 8, 11, 13, 11, 8, 5}, 
                                        {5, 8, 11, 13, 11, 8, 5},
                                        {4, 6, 8, 10, 8, 6, 4},
                                        {3, 4, 5, 7, 5, 4, 3}};

  // private functions:
  Node minimaxAB(Node position, int depth, bool player, int useThresh, int passThresh);
  bool deepEnough(Node position, int depth, bool player);
  int staticEval(bool player, Node position);
  vector<Node> moveGen(bool player, Node position);
  int winningMove(Node position, bool player);
  void drawBoard(vector<vector<int>>);
  char getPiece(int slot);
};

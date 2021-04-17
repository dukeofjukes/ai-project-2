/*
  Artifical Intelligence Project 2:
  Jeff Wilson
  Joe McAdams
  Brandon Burtchell

  Spring 2021
*/

#include "Project2.h"

int main()
{
  Connect4 game(2, 2, 1, 1, 276, 276);
  game.playGame();

  // TODO: reset and play each specified game

  return 0;
}

/*
  Connect4 class constructor
*/
Connect4::Connect4(int maxDepth, int minDepth, int maxStaticEval, int minStaticEval, int maxThresh, int minThresh)
{
  board.resize(ROWS, vector<int>(COLUMNS,0)); // define board size and initialize with 0's in every board location

  // set each player's minimax performance parameters:
  this->maxDepth = maxDepth;
  this->minDepth = minDepth;
  this->maxStaticEval = maxStaticEval;
  this->minStaticEval = minStaticEval;
  this->maxThresh = maxThresh;
  this->minThresh = minThresh;
}

/*
  Resets the relevant class variables to prepare for a new game.
*/
void Connect4::resetGame(int maxDepth, int minDepth, int maxStaticEval, int minStaticEval, int maxThresh, int minThresh) {
  board.clear();
  board.resize(ROWS, vector<int>(COLUMNS,0));

  // set each player's minimax performance parameters:
  this->maxDepth = maxDepth;
  this->minDepth = minDepth;
  this->maxStaticEval = maxStaticEval;
  this->minStaticEval = minStaticEval;
  this->maxThresh = maxThresh;
  this->minThresh = minThresh;
}

/*
  Plays and displays every turn of a single Connect4 game.
*/
void Connect4::playGame() 
{
  vector<vector<vector<int>>> moveHistory; // stores the history of a game to print at the end of a game.
  int winState = 0; // flags +1 for MAX victory, -1 for MIN victory
  int turnCount = 0;
  int maxTurns = COLUMNS * ROWS; // the number of turns before a draw occurs

  moveHistory.push_back(board); // save initial (empty) board

  Node move(board); // setup the state as the initial board
  while (turnCount < maxTurns)
  {
    // MAX's turn:
    move = minimaxAB(move, maxDepth, MAX, maxThresh, -(maxThresh)); // choose a move using minimax algorithm
    board = move.state; // play the move on the board
    moveHistory.push_back(move.state); // save the turn
    
    move.path.clear(); // free up memory
    turnCount++;

    // check if the move just played resulted in a win:
    if ((winState = winningMove(move, MAX)) != 0)
      break;

    // MIN's turn:
    move = minimaxAB(move, minDepth, MIN, minThresh, -(minThresh)); // choose a move using minimax algorithm
    board = move.state; // play the move on the board
    moveHistory.push_back(move.state); // save the turn
    
    move.path.clear(); // free up memory
    turnCount++;

    // check if the move just played resulted in a win:
    if ((winState = winningMove(move, MIN)) != 0)
      break;
  }

  // print moveHistory of the game:
  for (vector<vector<int>> m : moveHistory)
  {
    drawBoard(m);
  }

  // print winner:
  if (winState > 0) {
    cout << "GAME OVER: MAX (X) wins." << endl;
  } else if (winState < 0) {
    cout << "GAME OVER: MIN (O) wins." << endl;
  } else {
    cout << "GAME OVER: DRAW." << endl;
  }

  // free up memory:
  board.clear();
  moveHistory.clear();
}

// FIXME: clean up these comments when submitting:
// useThresh and passThresh alternate in the recursive call to reflect the relevant values for each player's best move evaluation
// player is true if it's player 1's (MAX) turn, false if player 2's (MIN) turn
// position = a node that holds a state of the board and an associated eval value; in connect4, a players "position" is the state of the entire game (the board)
Node Connect4::minimaxAB(Node position, int depth, bool player, int useThresh, int passThresh)
{
  if (deepEnough(position, depth, player))
  {
    //cout << "deepEnough returned true" << endl;
    Node n(position.state);
    n.value = staticEval(player, n); // calculate the score of this move

    /* // FIXME: placeholder of how different staticEvals will be used
    if (player == MAX)
    {
      switch(maxStaticEval)
      {
        case 1: n.value = staticEval1(player, n);
        case 2: n.value = staticEval2(player, n);
        case 3: n.value = staticEval3(player, n);
      }
    }
    else
    {
      switch(minStaticEval)
      {
        case 1: n.value = staticEval1(player, n);
        case 2: n.value = staticEval2(player, n);
        case 3: n.value = staticEval3(player, n);
      }
    }
    */

    //cout << "  end node static eval = " << n.value << endl;
    return n;
  }

  vector<Node> successors = moveGen(player, position); // generate another level of the tree

  if (successors.empty())
  {
    Node n(position.state);
    n.value = staticEval(player, n); // calculate the score of this move
    return n;
  }

  //cout << "Iterating through successors" << endl;
  int newValue;
  vector<vector<int>> bestMove = position.state;
  vector<Node> bestPath;
  for (Node succ : successors)
  {
    //cout << "Inside iterator" << endl;
    Node result_succ = minimaxAB(succ, depth - 1, !player, -(passThresh), -(useThresh)); // result_succ will be the best child of succ
    //cout << "result succ state: " << endl;
    //drawBoard(result_succ.state);
    //cout << "After recursive call, newValue to be set to " << -(result_succ.value) << endl;
    newValue = -(result_succ.value); // this node's newValue inherits its best child's best score
    //cout << "Testing newValue > passThresh" << endl;
    if (newValue > passThresh) // we have found a better successor, we need to record this for pruning (next succs in loop) and to pass it up the tree if it is indeed the best.
    {
      //cout << "newValue > passThresh; passThresh = newValue and bestPath set to result_succ.path" << endl;
      passThresh = newValue; // record the new best value as the limit for our pruning.
      //cout << "best value found" << passThresh << endl;
      bestPath = result_succ.path; // best path (so far) is now the path from this current succ to its children (succ.path).
      if (bestPath.empty())
      {
        bestPath.push_back(succ);
      }
      else
      {
        bestPath.insert(bestPath.begin(), succ); // add succ to the beginning of its child's path, since it will need to be returned to its parent as the best path
        bestMove = succ.state; // save this successor's state as the best move to make. the initial call will then return a Node with the best first move as the state
      }
    }
    //cout << "Testing passThresh > useThresh" << endl;
    if (passThresh >= useThresh) // is passThresh (the best value) is not better than useThresh, we should stop examining the parent's branch
    {
      //cout << "passThresh > useThresh was true, abandoning this branch and returning..." << endl;
      break; // we'll get out of this loop and return our best results
    } // else, try the next successor
  }

  Node n(bestMove); // FIXME: for future consideration: this might not be viable for minimax, but I wasn't sure how else to store the state of the node that held the best value and path
  n.value = passThresh; // passThresh will end up holding the best score so far
  n.path = bestPath; // always pass the best path to the parent
  return n;
}

bool Connect4::deepEnough(Node position, int depth, bool player)
{
  // depth is set to decrement for easier initialization of different depths per player
  if (depth <= 0 || winningMove(position, player) != 0 )
    return true;
  return false;
}


/* // FIXME: old random evaluation function:
int Connect4::staticEval(bool player, Node position)
{ //Defined to return a completely random evalutation number between 1 and 100
  int randEvalNumber = rand() % 100 + 1; //Number between 1 and 100
  return randEvalNumber;
}
*/

/*
  the static evaluation function, or the "heuristic"
  returns: a number respresenting the goodness of position from the standpoint of the player
*/
int Connect4::staticEval(bool player, Node position) {
  int utility = 138;
  int sum = 0;
  int pieceVal = (player) ? (1) : (-1);

  for (int col = 0; col < COLUMNS; col++)
  {
    for (int row = 0; row < ROWS; row++)
    {
      if (position.state[row][col] == pieceVal)
      {
        sum += evaluationTable[row][col];
      }
      else if (position.state[row][col] == -(pieceVal))
      {
        sum -= evaluationTable[row][col];
      }
    }
  }
  return utility + sum;
}

/*
  the plausible-move generator
  returns: a list of nodes representing moves that can be made
*/
vector<Node> Connect4::moveGen(bool player, Node position)
{
  vector<Node> successors;

  for (int col = 0; col < COLUMNS; col++)
  {
    for (int row = 0; row < ROWS; row++)
    {
      if (position.state[row][col] == 0) //Found the spot that isn't occupied in board; add to successors, break loop and analyze the next column
      {
        Node newNode = position; //Make a new node to contain the potential state. Potential state is the state of position + the move
        newNode.state[row][col] = (player) ? (1) : (-1); // add the player's piece that corresponds to this potential move
        successors.push_back(newNode); // add this succ to the successors list
        break;
      }
    }
  }
  
  return successors;
}

/*
  checks if position.state is a winning move for the player
  returns: the specific win state (max == +1, min == -1, none == 0) found in position.state
*/
int Connect4::winningMove(Node position, bool player)
{
  int piece = (player) ? (1) : (-1); // define whose win we are searching for

  // check horizontal:
  for (int col = 0; col < COLUMNS - 3; col++)
  {
    for (int row = 0; row < ROWS; row++)
    {
      if (position.state[row][col] == piece && position.state[row][col+1] == piece && position.state[row][col+2] == piece && position.state[row][col+3] == piece)
        return piece;
    }
  }

  // check vertical:
  for (int col = 0; col < COLUMNS; col++)
  {
    for (int row = 0; row < ROWS - 3; row++)
    {
      if (position.state[row][col] == piece && position.state[row+1][col] == piece && position.state[row+2][col] == piece && position.state[row+3][col] == piece)
        return piece;
    }
  }

  // check positive slope diagonal:
  for (int col = 0; col < COLUMNS - 3; col++)
  {
    for (int row = 0; row < ROWS - 3; row++)
    {
      if (position.state[row][col] == piece && position.state[row+1][col+1] == piece && position.state[row+2][col+2] == piece && position.state[row+3][col+3] == piece)
        return piece;
    }
  }

  // check negative slope diagonal:
  for (int col = 0; col < COLUMNS - 3; col++)
  {
    for (int row = 3; row < ROWS; row++)
    {
      if (position.state[row][col] == piece && position.state[row-1][col+1] == piece && position.state[row-2][col+2] == piece && position.state[row-3][col+3] == piece)
        return piece;
    }
  }

  return 0; // represents no victory
}

/*
  prints the entire game board in its current state
*/
void Connect4::drawBoard(vector<vector<int>> state)
{
  string line = "    -----------------------------";

  cout << endl;
  for (int i = ROWS - 1; i >= 0; i--)
  {
    cout << " " << i + 1 << "  ";
    for (int k = 0; k < COLUMNS; k++)
    {
      cout << "| " << getPiece(state[i][k]) << " ";
    }
    cout << "|" << endl;
    cout << line << endl;
  }
  cout << "      1   2   3   4   5   6   7" << endl;
}

/*
  helper function for displaying the game board
  returns: a char representation of a piece which occupies a given space/slot on the board
*/
char Connect4::getPiece(int slot)
{
  char piece;
  if (slot == 0)
  { // empty slot
    piece = ' ';
  }
  else if (slot > 0)
  { // X's piece
    piece = 'X';
  }
  else
  { // O's piece
    piece = 'O';
  }
  return piece;
}
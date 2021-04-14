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
  srand(time(NULL)); // initialize rand() seed

  Connect4 gameObj;
  gameObj.playGame();

  return 0;
}

Connect4::Connect4() // Constructor
{
  board.resize(ROWS, vector<int>(COLUMNS,0)); // define board size
  i = 0;
  cout << "initial board:" << endl;
  drawBoard(board);
}

void Connect4::playGame()
{
  vector<vector<vector<int>>> moveHistory; // stores the history of a game to print at the end of a game.
  Winner w = none; // utilizing the winner enumerator as a flag

  moveHistory.push_back(board);

  Node move(board);
  while (true) {
    // FIXME: toggle a bool instead of passing MAX and MIN
    move = minimaxAB(move, 0, MAX, 100, -100);
    updateBoard(move);
    moveHistory.push_back(move.state);
    if ((w = winningMove(move, MAX)) != none) break;

    move = minimaxAB(move, 0, MIN, 100, -100);
    updateBoard(move);
    moveHistory.push_back(move.state);
    if ((w = winningMove(move, MIN)) != none) break;
  }
  // TODO: print Winner w
  // FIXME: program hangs and never gets to a winningMove, I guess we need to implement staticEval for it to start working.

  for (vector<vector<int>> m : moveHistory)
  {
    drawBoard(m);
  }
}

void Connect4::updateBoard(Node move)
{
  this->board = move.state;
  
  /*
  cout << "game path as determined by minimax: " << endl;
  for (Node node : move.path)
  {
    drawBoard(node.state);
  }
  
  cout << "game board after one min max call (should reflect turn 1):" << endl;
  drawBoard(this->board);
  */
}

// useThresh and passThresh alternate in the recursive call to reflect the relevant values for each player's best move evaluation
// player is true if it's player 1's (MAX) turn, false if player 2's (MIN) turn
// position = a node that holds a state of the board and an associated eval value; in connect4, a players "position" is the state of the entire game (the board)
Node Connect4::minimaxAB(Node position, int depth, bool player, int useThresh, int passThresh)
{
  //this->i++; // FIXME: i no longer represents the depth in the tree, but the number of minimax calls being explored. more like the count of viable nodes idk
  //cout << "Entering minimaxAB" << endl;
  //cout << "Current state in recursion " << i << ": ";
  //drawBoard(position.state);

  if (deepEnough(position, depth, player)) // represents the case in which a final node depth is reached. will return from this final recursive call and begin constructing a path from the best node
  {
    //cout << "deepEnough returned true" << endl;
    Node n(position.state);
    n.value = staticEval(player, n); // calculate the score of this move
    // leave n.path empty, since it will be built by its recrursive parents
    return n;
  }

  //cout << "Generating successors" << endl;
  vector<Node> successors = moveGen(player, position); // generate another level of the tree
  //cout << "Successors generated" << endl;

  if (successors.empty())
  {
    cout << "Successors empty" << endl;
    Node n(position.state);
    n.value = staticEval(player, n); // calculate the score of this move
    // leave n.path empty, since it will be built by its recursive parents
    return n;
  }

  //cout << "Iterating through successors" << endl;
  // FIXME: could combine these variables into a Node object, which gets updated in the loop and returned at the end?
  int newValue;
  vector<vector<int>> bestMove = position.state;
  vector<Node> bestPath;
  for (Node succ : successors)
  {
    //cout << "Inside iterator" << endl;
    Node result_succ = minimaxAB(succ, depth + 1, !player, -(passThresh), -(useThresh)); // result_succ will be the best child of succ
    //cout << "result succ state: " << endl;
    //drawBoard(result_succ.state);
    // cout << "After recursive call, newValue to be set to " << -(result_succ.value) << endl;
    newValue = -(result_succ.value); // this node's newValue inherits its best child's best score
    //cout << "Testing newValue > passThresh" << endl;
    if (newValue > passThresh) // we have found a better successor, we need to record this for pruning (next succs in loop) and to pass it up the tree if it is indeed the best.
    {
      //cout << "newValue > passThresh; passThresh = newValue and bestPath set to result_succ.path" << endl;
      passThresh = newValue; // record the new best value as the limit for our pruning.
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
  if (depth == 2 /*|| winningMove(position) != none*/)
  {
    return true;
  }
  return false;
}

/*
  the static evaluation function, or the "heuristic"
  returns: a number respresenting the goodness of position from the standpoint of the player
*/
int Connect4::staticEval(bool player, Node position)
{ //Defined to return a completely random evalutation number between 1 and 100
  int randEvalNumber = rand() % 100 + 1; //Number between 1 and 100
  return randEvalNumber;
}

/*
  the plausible-move generator
  returns: a list of nodes representing moves that can be made
*/
vector<Node> Connect4::moveGen(bool player, Node position)
{
  vector<Node> successors;

  if (position.state[0][0] == 0 && position.state[0][1] == 0 && position.state[0][2] == 0 && position.state[0][3] == 0 && position.state[0][4] == 0 && position.state[0][5] == 0 && position.state[0][6] == 0) //If board is empty, successors is the entire first row
  {
    for (int col = 0; col < COLUMNS; col++)
    {
      for (int row = 0; row < 1; row++)
      {
        Node newNode = position; //Make a new node to contain the potential state. Potential state is the state of position + the move
        newNode.state[row][col] = (player) ? (1) : (-1); // add the player's piece that corresponds to this potential move
        successors.push_back(newNode); // add this succ to the successors list
      }
    }
  }
  else
  { //The board isn't empty, find available moves
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
  }
  
  return successors;
}

/*
  checks if position.state is a winning move (connected 4)
  returns: true of false depending on if the game is terminated at this state
*/
Winner Connect4::winningMove(Node position, bool player)
{
  int piece = (player) ? (1) : (-1); // define whose win we are searching for
  Winner winningPlayer = player ? Winner::max : Winner::min; // FIXME: why am i getting errors in this function when I don't type Winner:: ?????
  bool drawPossible = true; // flags false when an empty spot is found

  // check horizontal:
  for (int col = 0; col < COLUMNS - 3; col++)
  {
    for (int row = 0; row < ROWS; row++)
    {
      if (position.state[row][col] == 0)
      {
        drawPossible = false;
        break; // FIXME: break in order to avoid unnecessary row evaluations?
      }
      if (position.state[row][col] == piece && position.state[row][col+1] == piece && position.state[row][col+2] == piece && position.state[row][col+3] == piece)
        return winningPlayer;
    }
  }

  // check vertical:
  for (int col = 0; col < COLUMNS; col++)
  {
    for (int row = 0; row < ROWS - 3; row++)
    {
      if (position.state[row][col] == 0)
        drawPossible = false;
      if (position.state[row][col] == piece && position.state[row+1][col] == piece && position.state[row+2][col] == piece && position.state[row+3][col] == piece)
        return winningPlayer;
    }
  }

  // check positive slope diagonal:
  for (int col = 0; col < COLUMNS - 3; col++)
  {
    for (int row = 0; row < ROWS - 3; row++)
    {
      if (position.state[row][col] == piece && position.state[row+1][col+1] == piece && position.state[row+2][col+2] == piece && position.state[row+3][col+3] == piece)
        return winningPlayer;
    }
  }

  for (int col = 0; col < COLUMNS - 3; col++)
  {
    for (int row = 3; row < ROWS; row++)
    {
      if (position.state[row][col] == piece && position.state[row-1][col+1] == piece && position.state[row-2][col+2] == piece && position.state[row-3][col+3] == piece)
        return winningPlayer;
    }
  }

  if (drawPossible)
    return Winner::draw;

  return Winner::none;
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
      cout << "| " << getPiece(state[i][k]) << " "; //Pretty board for user view
      //cout << "| " << state[i][k] << " "; //For debugging
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
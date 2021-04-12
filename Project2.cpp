/*
  Artifical Intelligence Project 2:
  Jeff Wilson
  Joe McAdams
  Brandon Burtchell

  Spring 2021
*/

#include "Project2.h"
using namespace std;

int main()
{
  srand(time(NULL)); //initialize rand() seed
  Connect4 gameObj;


  cout << "initial board:" << endl;
  gameObj.drawBoard();

  gameObj.playGame();
  return 0;
}

Connect4::Connect4() //Constructor
{
  board.resize(ROWS, vector<int>(COLUMNS,0));
  i=0;
}

void Connect4::playGame()
{
  bool endCondition = false;
  Node initialNode(board);
  while(!endCondition)
  {

    Node move = minimaxAB(initialNode, 0, true, -100, 100);
    updateBoard(move);
    endCondition = true; //placeholder, 1 iteration. Need to check win condition/max turns (m*n)
  }
  //check win?
}

void Connect4::updateBoard(Node move)
{
  cout << "UPDATING BOARD: setting row/col on board from move" << endl;
  this->board = move.state;
  
  cout << "Showing states on path: " << endl;
  for (Node node : move.path)
  {
    string line = "    -----------------------------";
    cout << endl;
    for (int i = ROWS - 1; i >= 0; i--)
    {
      cout << " " << i + 1 << "  ";
      for (int k = 0; k < COLUMNS; k++)
      {
        cout << "| " << getPiece(node.state[i][k]) << " ";
      }
      cout << "|" << endl;
      cout << line << endl;
    }
  cout << "      1   2   3   4   5   6   7" << endl;
  }
  
  cout << "game board after one min max call:" << endl;
  drawBoard();
}

// useThresh is worst score for MAX (negative val)
// passThresh is worst score for MIN (positive val)
// player is true if it's player 1's (MAX) turn, false if player 2's (MIN) turn
// position = a node that holds a state of the board and an assosciated eval value; in connect4, a players position is the state of the entire game (the board)
Node Connect4::minimaxAB(Node position, int depth, bool player, int useThresh, int passThresh)
{
  this->i++;
  cout << "Entering minimaxAB" << endl;
  cout << "Current state in recursion " << i << ": ";
  string line = "    -----------------------------";

  cout << endl;
  for (int i = ROWS - 1; i >= 0; i--)
  {
    cout << " " << i + 1 << "  ";
    for (int k = 0; k < COLUMNS; k++)
    {
      cout << "| " << getPiece(position.state[i][k]) << " ";
    }
    cout << "|" << endl;
    cout << line << endl;
  }
  cout << "      1   2   3   4   5   6   7" << endl;

  //int posGameState[ROWS][COLUMNS]; 
  //copy(&gameState[0][0], &gameState[0][0]+ROWS*COLUMNS,&posGameState[0][0]); //Copy of paramater to use recursively
  if (deepEnough(depth))
  {
    cout << "deepEnough returned true" << endl;
    vector<Node> path; // create an empty path of game states
    position.path = path;
    return position;
  }

  cout << "Generating successors" << endl;
  vector<Node> successors = moveGen(player, position); // generate another level of the tree
  cout << "Successors generated" << endl;

  if (successors.empty())
  {
    cout << "Successors empty" << endl;
    vector<Node> path; // create an empty path of game states (a vector of boards (2d vectors))
    position.path = path;
    return position;
  }

  cout << "Iterating through successors" << endl;
  int newValue;
  vector<Node> bestPath;
  for (Node succ : successors)
  {
    cout << "Inside iterator" << endl;
    Node result_succ = minimaxAB(succ, depth + 1, !player, -(passThresh), -(useThresh));
    cout << "After recursive call, newValue to be set to " << -(result_succ.value) << endl;
    newValue = -(result_succ.value);
    cout << "Testing newValue > passThresh" << endl;
    if (newValue > passThresh)
    {
      cout << "newValue > passThresh; passThresh = newValue and bestPath set to result_succ.path" << endl;
      passThresh = newValue;
      bestPath = result_succ.path;
      bestPath.insert(bestPath.begin(), succ);
    }
    cout << "Testing passThresh > useThresh" << endl;
    if (passThresh >= useThresh)
    {
      cout << "passThresh > useThresh" << endl;
      position.value = passThresh;
      position.path = bestPath;
      return position;
    }
  }
  
  position.value = passThresh;
  position.path = bestPath;
  return position;
  
}

bool Connect4::deepEnough(int depth)
{
  // FIXME: determine what value represents a terminal node for position
  if (depth == 3 /*|| position == terminal node / game over*/)
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
        newNode.state[row][col] = 1; //+ the move. Unsure of how to represent; need to know which player and add a certain value that represents their move
        successors.push_back(newNode);
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
          newNode.state[row][col] = 1; //+ the move. Unsure of how to represent; need to know which player and add a certain value that represents their move
          successors.push_back(newNode);
          break;
        }
        else
          continue;
      }
    }
  }

  cout << "Successors states: " << endl;
  for (Node succ : successors)
  {
    string line = "    -----------------------------";

    cout << endl;
    for (int i = ROWS - 1; i >= 0; i--)
    {
      cout << " " << i + 1 << "  ";
      for (int k = 0; k < COLUMNS; k++)
      {
        cout << "| " << getPiece(succ.state[i][k]) << " ";
      }
      cout << "|" << endl;
      cout << line << endl;
    }
    cout << "      1   2   3   4   5   6   7" << endl;
  }
  return successors;
}

/*
  prints the entire game board in its current state
*/
void Connect4::drawBoard()
{
  string line = "    -----------------------------";

  cout << endl;
  for (int i = ROWS - 1; i >= 0; i--)
  {
    cout << " " << i + 1 << "  ";
    for (int k = 0; k < COLUMNS; k++)
    {
      cout << "| " << getPiece(this->board[i][k]) << " ";
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
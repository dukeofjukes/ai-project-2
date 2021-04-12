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
  srand(time(NULL)); //initialize rand() seed
  Connect4 gameObj;

  std::cout << "initial board:" << std::endl;
  gameObj.drawBoard();

  gameObj.playGame();
  return 0;
}

Connect4::Connect4() //Constructor
{
  // initialize board
  for (int i = 0; i < ROWS; i++)
  {
    for (int k = 0; k < COLUMNS; k++)
    {
      board[i][k] = 0;
    }
  }
}

void Connect4::playGame()
{
  Node move = minimaxAB(0, true, -100, 100);
  updateBoard(move);
  //check win?
}

void Connect4::updateBoard(Node move)
{
  board[move.row][move.col] = 1;
  for (Node node : move.path)
  {
    board[node.row][node.col] = 1; //testing to see if the board gets updated at all
  }
  std::cout << "board after one min max call:" << std::endl;
  this->drawBoard();
}

// useThresh is worst score for MAX (negative val)
// passThresh is worst score for MIN (positive val)
// player is true if it's player 1's (MAX) turn, false if player 2's (MIN) turn
Node Connect4::minimaxAB(int depth, bool player, int useThresh, int passThresh)
{
  std::cout << "Entering minimaxAB" << std::endl;

  if (deepEnough(depth))
  {
    std::cout << "deepEnough returned true" << std::endl;
    std::vector<Node> path; // create a null std::vector to pass to Node struct
    return Node(staticEval(player), path);
  }

  std::cout << "Generating successors" << std::endl;
  std::vector<Node> successors = moveGen(player); // generate another level of the tree
  std::cout << "Successors generated" << std::endl;

  if (successors.empty())
  {
    std::cout << "Successors empty" << std::endl;
    std::vector<Node> path; // create a null std::vector to pass to Node struct
    return Node(staticEval(player), path);
  }

  std::cout << "Iterating through successors" << std::endl;
  int newValue;
  std::vector<Node> bestPath;
  for (Node succ : successors)
  {
    std::cout << "Inside iterator" << std::endl;
    Node result_succ = minimaxAB(depth + 1, !player, -(passThresh), -(useThresh));
    std::cout << "After recursive call, newValue to be set to " << -(result_succ.value) << std::endl;
    newValue = -(result_succ.value);
    std::cout << "Testing newValue > passThresh" << std::endl;
    if (newValue > passThresh)
    {
      std::cout << "newValue > passThresh; passThresh = newValue and bestPath set to result_succ.path" << std::endl;
      passThresh = newValue;
      bestPath = result_succ.path;
      bestPath.insert(bestPath.begin(), succ);
    }
    std::cout << "Testing passThresh > useThresh" << std::endl;
    if (passThresh >= useThresh)
    {
      std::cout << "passThresh > useThresh" << std::endl;
      return Node(staticEval(player), succ.row, succ.col, bestPath);
    }
  }
  std::cout << "Reached base case, returning Node(passThresh, bestPath) where passThresh = " << passThresh << " and bestPath has nodes (row, col): " << std::endl;
  for (Node node : bestPath)
  {
    std::cout << node.row << ", " << node.col << std::endl;
  }
  return Node(passThresh, bestPath);
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
int Connect4::staticEval(bool player)
{ //Defined to return a completely random evalutation number between 1 and 100

  int randEvalNumber = rand() % 100 + 1; //Number between 1 and 100
  return randEvalNumber;
}

/*
  the plausible-move generator
  returns: a list of nodes representing moves that can be made
*/
std::vector<Node> Connect4::moveGen(bool player)
{
  std::vector<Node> successors;
  std::vector<Node> p; //empty path to initialize new nodes

  if (this->board[0][0] == 0 && this->board[0][1] == 0 && this->board[0][2] == 0 && this->board[0][3] == 0 && this->board[0][4] == 0 && this->board[0][5] == 0 && this->board[0][6] == 0) //If board is empty, successors is the entire first row
  {
    for (int col = 0; col < COLUMNS; col++)
    {
      for (int row = 0; row < 1; row++)
      {
        Node newNode(staticEval(player), row, col, p);
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
        if (this->board[row][col] == 0) //Found the spot that isn't occupied in board; add to successors, break loop and analyze the next column
        {
          Node newNode(staticEval(player), row, col, p);
          successors.push_back(newNode);
          break;
        }
        else
          continue;
      }
    }
  }

  std::cout << "Successors coordinates (row, col): " << std::endl;
  for (Node succ : successors)
  {
    std::cout << succ.row << ", " << succ.col << " v=" << succ.value << std::endl;
  }
  return successors;
}

/*
  prints the entire game board in its current state
*/
void Connect4::drawBoard()
{
  std::string line = "    -----------------------------";

  std::cout << std::endl;
  for (int i = ROWS - 1; i >= 0; i--)
  {
    std::cout << " " << i + 1 << "  ";
    for (int k = 0; k < COLUMNS; k++)
    {
      std::cout << "| " << getPiece(this->board[i][k]) << " ";
    }
    std::cout << "|" << std::endl;
    std::cout << line << std::endl;
  }
  std::cout << "      1   2   3   4   5   6   7" << std::endl;
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
/*
  Artifical Intelligence Project 2:
  Jeff Wilson
  Joe McAdams
  Brandon Burtchell

  Spring 2021
*/

#include "Project2.h"

int main() {
  Connect4 gameObj;
  gameObj.initializeBoard();

  std::cout << "initial board:" << std::endl;
  gameObj.drawBoard();

  gameObj.playGame();
  return 0;
}


Connect4::Connect4() //Constructor
{

}

void Connect4::playGame()
{
  Node move = minimaxAB(0, 0, 0, true, -100, 100);
  updateBoard(move);
}

void Connect4::initializeBoard()
{
  for (int i = 0; i < COLUMNS; i++) { 
    for (int k = 0; k < ROWS; k++) {
      board[i][k] = 0;
    }
  }
}

void Connect4::updateBoard(Node move)
{
  for(Node node : move.path)
  {
    board[node.col][node.row] = 1; //testing to see if the board gets updated at all
  }
  std::cout << "board after one min max call:" << std::endl;
  this->drawBoard();
}

// useThresh is worst score for MAX (negative val)
// passThreshh is worst score for MIN (positive val)
Node Connect4::minimaxAB(int row, int col, int depth, bool player, int useThresh, int passThresh) {
  if (deepEnough(row, col, depth)) {
    std::vector<Node> path; // create a null std::vector to pass to Node struct
    return Node(staticEval(row, col, player), path);
  }
  
  std::vector<Node> successors = moveGen(row, col, player); // generate another level of the tree

  if (successors.empty()) {
    std::vector<Node> path; // create a null std::vector to pass to Node struct
    return Node(staticEval(row, col, player), path);
  }
  
  int newValue;
  std::vector<Node> bestPath;
  for (Node succ : successors) {
    Node result_succ = minimaxAB(succ.row, succ.col, depth + 1, !player, -(passThresh), -(useThresh));
    newValue = -(result_succ.value);
    if (newValue > passThresh) {
      newValue = passThresh;
      bestPath = result_succ.path;
      bestPath.insert(bestPath.begin(), succ);
    }

    if (passThresh >= useThresh) {
      break;
    }
  }

  return Node(passThresh, bestPath);
}

bool Connect4::deepEnough(int row, int col, int depth) {
  // FIXME: determine what value represents a terminal node for position
  if (depth == 5 /*|| position == terminal node / game over*/) {
    return true;
  }
  return false;
}

/*
  the static evaluation function, or the "heuristic"
  returns: a number respresenting the goodness of position from the standpoint of the player
*/
int Connect4::staticEval(int row, int col, bool player) { //Defined to return a completely random evalutation number between 1 and 100
  
  srand (time(NULL));
  int randEvalNumber = rand()%100 + 1; //Number between 1 and 100
  return randEvalNumber; 
}

/*
  the plausible-move generator
  returns: a list of nodes representing moves that can be made
*/
std::vector<Node> Connect4::moveGen(int row, int col, bool player) {
  std::vector<Node> successors;
  std::vector<Node> p;
  if (this->board[0][0] == 0 && this->board[0][1] == 0 && this->board[0][2] == 0 && this->board[0][3] == 0 && this->board[0][4] == 0 && this->board[0][5] == 0) //If board is empty, successors is the entire first row
  {
    for(int column = 0; column < COLUMNS; column++)
    {
      for(int row = 0; row < 1; row++)
      {
        Node newNode(0, p);
        newNode.row = row;
        newNode.col = column;
        successors.push_back(newNode);
      }
    }
  }
  else  //The board isn't empty, find available moves
  for(int column = 0; column < COLUMNS; column++)
    {
      for(int row = 0; row < ROWS; row++)
      {
        if(this->board[column][row] == 0) //Found the spot that isn't occupied in board; add to successors, break loop and analyze the next column
          {
            Node newNode(0, p);
            newNode.row = row;
            newNode.col = column;
            successors.push_back(newNode);
            break;
          }
        else continue;
      }
    }

  return successors;
}

/*
  prints the entire game board in its current state
*/
void Connect4::drawBoard() {
  std::string line = "    -----------------------------";

  std::cout << std::endl;
  for (int i = ROWS - 1; i >= 0; i--) {
    std::cout << " " << i + 1 << "  ";
    for (int k = 0; k < COLUMNS; k++) {
      std::cout << "| " << getPiece(this->board[k][i]) << " ";
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
char Connect4::getPiece(int slot) {
  char piece;
  if (slot == 0) { // empty slot
    piece = ' ';
  } else if (slot > 0) { // X's piece
    piece = 'X';
  } else { // O's piece
    piece = 'O';
  }
  return piece;
}
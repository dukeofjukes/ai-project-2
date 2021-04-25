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
  char quitInput;
  bool quit = false;
  int driverControl;
  int maxDepth, minDepth, maxStaticEval, minStaticEval, maxThresh, minThresh;

  cout << "--- Welcome to CONNECT FOUR: MINIMAX Edition ---" << endl;
  cout << "If you'd like to manually enter parameters for each game enter 1, otherwise enter 0: ";
  cin >> driverControl;
  if (driverControl == 1)
  {
    while (!quit)
    {
      cout << endl << "Set game parameters:" << endl;
      cout << "  Player MAX's cutoff depth (choose 2, 4, or 8): ";
      cin >> maxDepth;
      cout << "  Player MIN's cutoff depth (choose 2, 4, or 8): ";
      cin >> minDepth;
      cout << "  Player MAX's evaluation function (choose 1, 2, or 3): ";
      cin >> maxStaticEval;
      cout << "  Player MIN's evaluation function (choose 1, 2, or 3): ";
      cin >> minStaticEval;

      // set threshold values once eval functions are done
      if (maxStaticEval == 1)
        maxThresh = 276;
      else if (maxStaticEval == 2)
        maxThresh = 1000;
      else
        maxThresh = 400;
      
      if (minStaticEval == 1)
        minThresh = 276;
      else if (minStaticEval == 2)
        minThresh = 1000;
      else
        minThresh = 400;

      Connect4 game(maxDepth, minDepth, maxStaticEval, minStaticEval, maxThresh, minThresh);

      cout << endl << "GAME " << Connect4::gameCounter + 1 << ":" << endl;
      game.playGame();

      cout << "Play another game (choose Y/N)? ";
      cin >> quitInput;
      if (quitInput == 'n' || quitInput == 'N')
        break;
    }
  }
  else
  {
    // game 1:
    Connect4 game1(2, 2, 1, 2, 276, 1000);
    cout << "GAME " << Connect4::gameCounter + 1 << ":" << endl;
    cout << "(MAX (eval #1) with depth 2 vs. MIN (eval #2) with depth 2)" << endl;
    game1.playGame();
    cout << "Press enter to continue.";
    cin.ignore();

    // game 2:
    Connect4 game2(2, 4, 1, 3, 276, 400);
    cout << "GAME " << Connect4::gameCounter + 1 << ":" << endl;
    cout << "(MAX (eval #1) with depth 2 vs. MIN (eval #3) with depth 4)" << endl;
    game2.playGame();
    cout << "Press enter to continue.";
    cin.ignore();

    // game 3:
    Connect4 game3(2, 8, 2, 3, 1000, 400);
    cout << "GAME " << Connect4::gameCounter + 1 << ":" << endl;
    cout << "(MAX (eval #2) with depth 2 vs. MIN (eval #3) with depth 8)" << endl;
    game3.playGame();
    cout << "Press enter to continue.";
    cin.ignore();

    // game 4:
    Connect4 game4(4, 2, 1, 2, 276, 1000);
    cout << "GAME " << Connect4::gameCounter + 1 << ":" << endl;
    cout << "(MAX (eval #1) with depth 4 vs. MIN (eval #2) with depth 2)" << endl;
    game4.playGame();
    cout << "Press enter to continue.";
    cin.ignore();

    // game 5:
    Connect4 game5(4, 4, 1, 3, 276, 400);
    cout << "GAME " << Connect4::gameCounter + 1 << ":" << endl;
    cout << "(MAX (eval #1) with depth 4 vs. MIN (eval #3) with depth 4)" << endl;
    game5.playGame();
    cout << "Press enter to continue.";
    cin.ignore();

    // game 6:
    Connect4 game6(4, 8, 2, 3, 1000, 400);
    cout << "GAME " << Connect4::gameCounter + 1 << ":" << endl;
    cout << "(MAX (eval #2) with depth 4 vs. MIN (eval #3) with depth 8)" << endl;
    game6.playGame();
    cout << "Press enter to continue.";
    cin.ignore();

    // game 7:
    Connect4 game7(8, 2, 1, 2, 276, 1000);
    cout << "GAME " << Connect4::gameCounter + 1 << ":" << endl;
    cout << "(MAX (eval #1) with depth 8 vs. MIN (eval #2) with depth 2)" << endl;
    game7.playGame();
    cout << "Press enter to continue.";
    cin.ignore();

    // game 8:
    Connect4 game8(8, 4, 1, 3, 276, 400);
    cout << "GAME " << Connect4::gameCounter + 1 << ":" << endl;
    cout << "(MAX (eval #1) with depth 8 vs. MIN (eval #3) with depth 4)" << endl;
    game8.playGame();
    cout << "Press enter to continue.";
    cin.ignore();

    // game 9:
    Connect4 game9(8, 8, 2, 3, 1000, 400);
    cout << "GAME " << Connect4::gameCounter + 1 << ":" << endl;
    cout << "(MAX (eval #2) with depth 8 vs. MIN (eval #3) with depth 8)" << endl;
    game9.playGame();
  }

  // print overall statistics:
  cout << endl;
  cout << "OVERALL STATISTICS: " << endl;
  cout << "  Total games:  " << Connect4::gameCounter << endl;
  cout << "  MAX (X) wins: " << Connect4::maxWins << endl;
  cout << "  MIN (O) wins: " << Connect4::minWins << endl;
  cout << "  Draws:        " << Connect4::draws << endl;

  return 0;
}

// Connect4 static variable initialization:
int Connect4::maxWins = 0;
int Connect4::minWins = 0;
int Connect4::draws = 0;
int Connect4::gameCounter = 0;

/*
  Connect4 class constructor
*/
Connect4::Connect4(int maxDepth, int minDepth, int maxStaticEval, int minStaticEval, int maxThresh, int minThresh)
{
  // initialize statistic variables:
  this->turnCounter = 0;
  this->nodeCounter = 0;
  this->gameDuration = 0;

  //initialize random
  srand(time(NULL));

  // define board size and initialize with 0's in every board location
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
  int winState = 0; // flags +1 for MAX victory, -1 for MIN victory
  int maxTurns = COLUMNS * ROWS; // the number of turns before a draw occurs

  this->gameCounter++;
  auto start = chrono::steady_clock::now();
  Node move(board); // setup the state as the initial board
  this->nodeCounter++;
  while (turnCounter < maxTurns)
  {
    // MAX's turn:
    this->turnCounter++;
    this->currentPlayerStaticEval = maxStaticEval;
    cout << "MAX'S (X) TURN (" << turnCounter << "):" << endl;
    move = minimaxAB(move, maxDepth, MAX, maxThresh, -(maxThresh)); // choose a move using minimax algorithm
    board = move.state; // play the move on the board
    drawBoard(board); // display to screen
    
    move.path.clear(); // free up memory

    // check if the move just played resulted in a win:
    if ((winState = winningMove(move, MAX)) != 0)
      break;

    // MIN's turn:
    this->turnCounter++;
    this->currentPlayerStaticEval = minStaticEval;
    cout << "MIN'S (O) TURN (" << turnCounter << "):" << endl;
    move = minimaxAB(move, minDepth, MIN, minThresh, -(minThresh)); // choose a move using minimax algorithm
    board = move.state; // play the move on the board
    drawBoard(board); // display to screen
    
    move.path.clear(); // free up memory

    // check if the move just played resulted in a win:
    if ((winState = winningMove(move, MIN)) != 0)
      break;
  }
  auto end = chrono::steady_clock::now();
  this->gameDuration = chrono::duration_cast<chrono::milliseconds>(end - start).count();

  // print winner:
  if (winState > 0)
  {
    cout << "GAME OVER: MAX (X) wins." << endl;
    this->maxWins++;
  }
  else if (winState < 0)
  {
    cout << "GAME OVER: MIN (O) wins." << endl;
    this->minWins++;
  }
  else
  {
    cout << "GAME OVER: DRAW." << endl;
    this->draws++;
  }

  // print game statistics:
  cout << endl;
  cout << "GAME " << Connect4::gameCounter << " STATISTICS:" << endl;
  cout << "  Number of turns: " << turnCounter << endl;
  cout << "  Nodes created:   " << nodeCounter << endl;
  cout << "  Game duration:   " << gameDuration << " msec" << endl;

  // free up memory:
  board.clear();
}

/*
  A recursive function that determines the "best" move to make from the standpoint of its initial
  call. Utilizes multiple helper variables.
  returns: the Node containing the best next move as determined by staticEval().
*/
Node Connect4::minimaxAB(Node position, int depth, bool player, int useThresh, int passThresh)
{
  if (deepEnough(position, depth, player))
  {
    Node n(position.state, position.moveRowCoord, position.moveColCoord);
    n.value = staticEval(player, n); // calculate the score of this move
    return n;
  }

  vector<Node> successors = moveGen(player, position); // generate another level of the tree

  if (successors.empty())
  {
    Node n(position.state, position.moveRowCoord, position.moveColCoord);
    n.value = staticEval(player, n); // calculate the score of this move
    return n;
  }

  // holder variables to be returned after the successor loop:
  int newValue;
  vector<vector<int>> bestMove = position.state;
  vector<Node> bestPath;

  for (Node succ : successors)
  {
    Node result_succ = minimaxAB(succ, depth - 1, !player, -(passThresh), -(useThresh)); // result_succ will be the best child of succ
    newValue = -(result_succ.value); // this node's newValue inherits its best child's best score
    if (newValue > passThresh) // we have found a better successor, we need to record this for pruning (next succs in loop) and to pass it up the tree if it is indeed the best.
    {
      bestMove = succ.state; // save this successor's state as the best move to make.
      passThresh = newValue; // record the new best value as the limit for our pruning.
      bestPath = result_succ.path; // best path is now the path from this current succ to its children
      if (bestPath.empty())
        bestPath.push_back(succ);
      else
        bestPath.insert(bestPath.begin(), succ); // add succ to the beginning of its child's path, since it will need to be returned to its parent as the best path
    }

    if (passThresh >= useThresh) // is passThresh (the best value) is not better than useThresh, we should stop examining the parent's branch
      break;
  }

  // if a best node was never set/found, default to the first value in successors
  if (bestMove == position.state)
    bestMove = successors[0].state;

  Node n(bestMove);
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

/*
  the static evaluation function, or the "heuristic"
  contains three seperate evaluation functions developed by each group member, nested in a case-switch
  returns: a number respresenting the goodness of position from the standpoint of the player
*/
int Connect4::staticEval(bool player, Node position)
{
  // global case vars:
  int pieceVal = (player) ? (1) : (-1);
  int winningPlayer = winningMove(position, player);
  
  // case 1 vars:
  int sum = 0;

  // case 2 vars:
  int random = rand() % 500 + 1; //Random value between 500 and 1 (to avoid picking leftmost node every time)
  int inARowCountLeftO = 0;
  int inARowCountRightO = 0;
  int inARowCountPosO = 0;
  int inARowCountNegO = 0;
  int inARowCountLeftP = 0;
  int inARowCountRightP = 0;
  int inARowCountPosP = 0;
  int inARowCountNegP = 0;
  int moveValue = 0;

  // case 3 vars:
  int currMoveVal = 0;

  // uses the proper evaluation function depending on what was defined for this player for this game
  switch(currentPlayerStaticEval)
  {
    case 1: /* AUTHOR: Brandon Burtchell */
      if (winningPlayer == pieceVal)
        return utility * 2; // best-case scenario
      else if (winningPlayer == -pieceVal)
        return 0; // worst-case scenario

      for (int col = 0; col < COLUMNS; col++)
      {
        for (int row = 0; row < ROWS; row++)
        {
          if (position.state[row][col] == pieceVal)
            sum += evaluationTable[row][col];
          else if (position.state[row][col] == -(pieceVal))
            sum -= evaluationTable[row][col];
        }
      }

      return utility + sum;

    case 2: /* AUTHOR: Joe McAdams */
      /*Analyzes the board for amount in a row the state being evaluated will give for player or block for opponent.
        Returns the biggest value determined for the state (I.E if a move would block 3 in a row and also block 2 in a row, it's valued for blocking 3 in a row)*/
      pieceVal = -(pieceVal);
      winningPlayer = -(winningPlayer);

      if (winningPlayer == pieceVal) //If this move would result in a win, return best score
        return -(winningMoveScore);

      /*Check for opponent pieces in rows*/
      //Check if move blocks x in a row of opponent vertically (below)
      if (position.moveRowCoord >= ROWS - 3 && position.state[position.moveRowCoord - 1][position.moveColCoord] == -pieceVal && position.state[position.moveRowCoord - 2][position.moveColCoord] == -pieceVal && position.state[position.moveRowCoord - 3][position.moveColCoord] == -pieceVal) 
        if (moveValue < blockingWinningMove)
          moveValue = blockingWinningMove; //State blocks opponent winning move, moveValue blockingWinningMove
      else if (position.moveRowCoord >= ROWS - 4 && position.state[position.moveRowCoord - 1][position.moveColCoord] == -pieceVal && position.state[position.moveRowCoord - 2][position.moveColCoord] == -pieceVal)
        if (moveValue < blockingThreeInRow)
          moveValue = blockingThreeInRow; //State blocks the opponents 3 in a row, moveValue = blockingThreeInRow
      else if (position.moveRowCoord >= ROWS - 5 && position.state[position.moveRowCoord - 1][position.moveColCoord] == -pieceVal)
        if (moveValue < blockingTwoInRow)
          moveValue = blockingTwoInRow; //State blocks opponent 2 in a row, moveValue = blockingThreeInRow

      //Check if move blocks x in a row of opponent horizontally - to the left
      if (position.moveColCoord >= COLUMNS - 4 && position.state[position.moveRowCoord][position.moveColCoord - 1] == -pieceVal && position.state[position.moveRowCoord][position.moveColCoord - 2] == -pieceVal && position.state[position.moveRowCoord][position.moveColCoord - 3] == -pieceVal) 
        if (moveValue < blockingWinningMove) 
          moveValue = blockingWinningMove; //State blocks opponent winning move, moveValue blockingWinningMove
      else if (position.moveColCoord >= COLUMNS - 5 && position.state[position.moveRowCoord][position.moveColCoord - 1] == -pieceVal && position.state[position.moveRowCoord][position.moveColCoord - 2] == -pieceVal)
      {
        inARowCountLeftO = 2;
        if (moveValue < blockingThreeInRow) 
          moveValue = blockingThreeInRow; //State blocks the opponents 3 in a row, moveValue = blockingThreeInRow
      }
      else if (position.moveColCoord >= COLUMNS - 6 && position.state[position.moveRowCoord][position.moveColCoord - 1] == -pieceVal)
      {
        if (inARowCountLeftO == 0) inARowCountLeftO = 1;
        if (moveValue < blockingTwoInRow) 
          moveValue = blockingTwoInRow; //State blocks opponent 2 in a row, moveValue = blockingThreeInRow
      }

      //Check if move blocks x in a row of opponent horizontally - to the right
      if (position.moveColCoord <= COLUMNS - 4 && position.state[position.moveRowCoord][position.moveColCoord + 1] == -pieceVal && position.state[position.moveRowCoord][position.moveColCoord + 2] == -pieceVal && position.state[position.moveRowCoord][position.moveColCoord + 3] == -pieceVal) 
        if (moveValue < blockingWinningMove) 
          moveValue = blockingWinningMove; //State blocks opponent winning move, moveValue blockingWinningMove
      else if (position.moveColCoord <= COLUMNS - 3 && position.state[position.moveRowCoord][position.moveColCoord + 1] == -pieceVal && position.state[position.moveRowCoord][position.moveColCoord + 2] == -pieceVal)
      {
        inARowCountRightO = 2;
        if (moveValue < blockingThreeInRow) 
          moveValue = blockingThreeInRow; //State blocks the opponents 3 in a row, moveValue = blockingThreeInRow
      }
      else if (position.moveColCoord <= COLUMNS - 2 && position.state[position.moveRowCoord][position.moveColCoord + 1] == -pieceVal)
      {
        if (inARowCountRightO == 0) inARowCountRightO = 1;
        if (moveValue < blockingTwoInRow)
          moveValue = blockingTwoInRow; //State blocks opponent 2 in a row, moveValue = blockingThreeInRow
      }

      if (inARowCountRightO + inARowCountLeftO >= 3 && moveValue < blockingWinningMove) moveValue = blockingWinningMove;
      else if (inARowCountRightO + inARowCountLeftO == 2 && moveValue < blockingThreeInRow) moveValue = blockingThreeInRow;
      //else it's already blockingTwoInRow or not blocking anything

      //Check if move blocks x in a row of a opponent diagonally (positive slope)
      if (position.moveColCoord <= COLUMNS - 4 && position.moveRowCoord <= ROWS - 4 && position.state[position.moveRowCoord + 1][position.moveColCoord + 1] == -pieceVal && position.state[position.moveRowCoord + 2][position.moveColCoord + 2] == -pieceVal && position.state[position.moveRowCoord + 3][position.moveColCoord + 3] == -pieceVal) 
        if (moveValue < blockingWinningMove)
          moveValue = blockingWinningMove; //State blocks opponent winning move, moveValue blockingWinningMove
      else if (position.moveColCoord <= COLUMNS - 3 && position.moveRowCoord <= ROWS - 3 && position.state[position.moveRowCoord + 1][position.moveColCoord + 1] == -pieceVal && position.state[position.moveRowCoord + 2][position.moveColCoord + 2] == -pieceVal)
      {
        inARowCountPosO = 2;
        if (moveValue < blockingThreeInRow)
          moveValue = blockingThreeInRow; //State blocks the opponents 3 in a row, moveValue = blockingThreeInRow
      }
      else if (position.moveColCoord <= COLUMNS - 2 && position.moveRowCoord <= ROWS - 2 && position.state[position.moveRowCoord + 1][position.moveColCoord + 1] == -pieceVal)
      {
        if (inARowCountPosO == 0) inARowCountPosO = 1;
        if (moveValue < blockingTwoInRow)
          moveValue = blockingTwoInRow; //State blocks opponent 2 in a row, moveValue = blockingThreeInRow
      }

      //Check if move blocks x in a row of a opponent diagonally (Negative slope)
      if (position.moveColCoord >= COLUMNS - 4 && position.moveRowCoord >= ROWS - 3 && position.state[position.moveRowCoord - 1][position.moveColCoord - 1] == -pieceVal && position.state[position.moveRowCoord - 2][position.moveColCoord - 2] == -pieceVal && position.state[position.moveRowCoord - 3][position.moveColCoord - 3] == -pieceVal) 
        if (moveValue < blockingWinningMove)
          moveValue = blockingWinningMove; //State blocks opponent winning move, moveValue blockingWinningMove
      else if (position.moveColCoord >= COLUMNS - 5 && position.moveRowCoord >= ROWS - 4 && position.state[position.moveRowCoord - 1][position.moveColCoord - 1] == -pieceVal && position.state[position.moveRowCoord - 2][position.moveColCoord - 2] == -pieceVal)
      {
        inARowCountNegO = 2;
        if (moveValue < blockingThreeInRow)
          moveValue = blockingThreeInRow; //State blocks the opponents 3 in a row, moveValue = blockingThreeInRow
      }
      else if (position.moveColCoord >= COLUMNS - 6 && position.moveRowCoord >= ROWS - 5 && position.state[position.moveRowCoord - 1][position.moveColCoord - 1] == -pieceVal)
      {
        if(inARowCountNegO == 0) inARowCountNegO = 1;
        if (moveValue < blockingTwoInRow)
          moveValue = blockingTwoInRow; //State blocks opponent 2 in a row, moveValue = blockingThreeInRow
      }
      
      if (inARowCountNegO + inARowCountPosO >= 3 && moveValue < blockingWinningMove) moveValue = blockingWinningMove;
      else if (inARowCountNegO + inARowCountPosO == 2 && moveValue < blockingThreeInRow) moveValue = blockingThreeInRow;
      //else it's already blockingTwoInRow or not blocking anything
      
      /*Check for player pieces in rows*/
      //Check if move gives x in a row vertically (below)
      if (position.moveRowCoord >= ROWS - 4 && position.state[position.moveRowCoord - 1][position.moveColCoord] == pieceVal && position.state[position.moveRowCoord - 2][position.moveColCoord] == pieceVal)
        if (moveValue < gettingThreeInRow)
          moveValue = gettingThreeInRow; //State gives player 3 in a row, moveValue = gettingThreeInRow
      else if (position.moveRowCoord >= ROWS - 5 && position.state[position.moveRowCoord - 1][position.moveColCoord] == pieceVal)
        if (moveValue < gettingTwoInRow)
          moveValue = gettingTwoInRow; //State gives player 2 in a row, moveValue = gettingTwoInRow

      //Check if move gives x in a row horizontally - to the left
      if (position.moveColCoord >= COLUMNS - 5 && position.state[position.moveRowCoord][position.moveColCoord - 1] == pieceVal && position.state[position.moveRowCoord][position.moveColCoord - 2] == pieceVal)
      {
        inARowCountLeftP = 2;
        if (moveValue < gettingThreeInRow)
          moveValue = gettingThreeInRow; //State gives player 3 in a row, moveValue = gettingThreeInRow
      }
      else if (position.moveColCoord >= COLUMNS - 6 && position.state[position.moveRowCoord][position.moveColCoord - 1] == pieceVal)
      {
        if(inARowCountLeftP == 0) inARowCountLeftP = 1;
        if (moveValue < gettingTwoInRow)
          moveValue = gettingTwoInRow; //State gives player 2 in a row, moveValue = gettingTwoInRow
      }

      //Check if move gives x in a row horizontally - to the right
      if (position.moveColCoord <= COLUMNS - 3 && position.state[position.moveRowCoord][position.moveColCoord + 1] == pieceVal && position.state[position.moveRowCoord][position.moveColCoord + 2] == pieceVal)
      {
        inARowCountRightP = 2;
        if (moveValue < gettingThreeInRow)
          moveValue = gettingThreeInRow; //State gives player 3 in a row, moveValue = gettingThreeInRow
      }
      else if (position.moveColCoord <= COLUMNS - 2 && position.state[position.moveRowCoord][position.moveColCoord + 1] == pieceVal)
      {
        if(inARowCountRightP == 0) inARowCountRightP = 1;
        if (moveValue < gettingTwoInRow)
          moveValue = gettingTwoInRow; //State gives player 2 in a row, moveValue = gettingThreeInRow
      }

      if (inARowCountRightP + inARowCountLeftP >= 3 && moveValue < winningMoveScore) moveValue = winningMoveScore;
      else if (inARowCountRightP + inARowCountLeftP == 2 && moveValue < gettingThreeInRow) moveValue = gettingThreeInRow;
      //else it's already gettingTwoInRow or none in row

      //Check if move gives x in a row diagonally - positive slope
      if (position.moveColCoord <= COLUMNS - 3 && position.moveRowCoord <= ROWS - 3 && position.state[position.moveRowCoord + 1][position.moveColCoord + 1] == pieceVal && position.state[position.moveRowCoord + 2][position.moveColCoord + 2] == pieceVal)
      {
        inARowCountPosP = 2;
        if (moveValue < gettingThreeInRow)
          moveValue = gettingThreeInRow; //State gives player 3 in a row, moveValue = gettingThreeInRow
      }
      else if (position.moveColCoord <= COLUMNS - 2 && position.moveRowCoord <= ROWS - 2 && position.state[position.moveRowCoord + 1][position.moveColCoord + 1] == pieceVal)
      {
        if (inARowCountPosP == 0) inARowCountPosP = 1;
        if (moveValue < gettingTwoInRow)
          moveValue = gettingTwoInRow; //State gives player 2 in a row, moveValue = gettingTwoInRow
      }

      //Check if move gives x in a row diagonally - negative slope
      if (position.moveColCoord >= COLUMNS - 5 && position.moveRowCoord >= ROWS - 4 && position.state[position.moveRowCoord - 1][position.moveColCoord - 1] == pieceVal && position.state[position.moveRowCoord - 2][position.moveColCoord - 2] == pieceVal)
      { 
        inARowCountNegP = 2;
        if (moveValue < gettingThreeInRow)
          moveValue = gettingThreeInRow; //State gives player 3 in a row, moveValue = gettingThreeInRow
      }
      else if (position.moveColCoord >= COLUMNS - 6 && position.moveRowCoord >= ROWS - 5 && position.state[position.moveRowCoord - 1][position.moveColCoord - 1] == pieceVal)
      {
        if (inARowCountNegP == 0) inARowCountNegP = 1;
        if (moveValue < gettingTwoInRow)
          moveValue = gettingTwoInRow; //State gives player 2 in a row, moveValue = gettingTwoInRow
      }
      
      if (inARowCountPosP + inARowCountNegP >= 3 && moveValue < winningMoveScore) moveValue = winningMoveScore;
      else if (inARowCountPosP + inARowCountNegP == 2 && moveValue < gettingThreeInRow) moveValue = gettingThreeInRow;
      //else it's already gettingTwoInRow or none in row
      
      //default - just return the lowest score
      if (moveValue < random)
        moveValue = random;

      return -(moveValue);
      
    case 3: /* AUTHOR: Jeff Wilson */
      pieceVal = -(pieceVal);
      winningPlayer = -(winningPlayer);

      if (winningPlayer == pieceVal) // if this move would result in a win, return best score
        return -(winningScore);

      if ((position.moveRowCoord - 1) >= 0 && position.state[position.moveRowCoord - 1][position.moveColCoord] == -(pieceVal)) 
      {
        // The piece under the current piece is an enemy piece so play on top of it.
        currMoveVal = blockOpponentVertically_DEFENSE;
      }
      else if (position.moveColCoord % 2 != 0)
      {
        // No chance to block, play an even column (with columns 1-7, to account for off-by-one error)
        currMoveVal = playEvenColumn;
      }
      else if (position.moveColCoord % 2 == 0)
      {
        // No chance to block, play an odd column (with columns 1-7, to account for off-by-one error)
        currMoveVal = playOddColumn;
      }

      return -(currMoveVal);
  }
  return 0; // something went wrong
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
      if (position.state[row][col] == 0) // found the spot that isn't occupied in board
      {
        Node newNode = position; // make a new node to contain the potential state. Potential state is the state of position + the move
        newNode.state[row][col] = (player) ? (1) : (-1); // add the player's piece that corresponds to this potential move
        newNode.moveRowCoord = row;
        newNode.moveColCoord = col;
        successors.push_back(newNode); // add this succ to the successors list
        this->nodeCounter++;
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
  cout << "      1   2   3   4   5   6   7" << endl << endl;
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
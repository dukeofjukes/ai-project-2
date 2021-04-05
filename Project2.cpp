/*
  Artifical Intelligence Project 2:
  Jeff Wilson
  Joe McAdams
  Brandon Burtchell

  Spring 2021
*/

#include "Project2.h"
using namespace std;

struct Node {
  int value;
  int path;

  Node(int v, int p) {
    value = v;
    path = p; // FIXME; should this be a list? or just point to next node?
  }
};

// function declarations:
Node minimaxAB(int position, int depth, bool player, int useThresh, int passThresh);
bool deepEnough(int position, int depth);
int staticEval(int position, bool player);
Node* moveGen(int position, bool player);
//drawBoard(...);

//TODO: for each group member, define evaluation functions (print tables to a file?)

int main() {
  return 0;
}

Node minimaxAB(int position, int depth, bool player, int useThresh, int passThresh) {
  if (deepEnough(position, depth)) {
    // FIXME: need to determine a value for int path ~= NULL, using 0 as placeholder
    return Node(staticEval(position, player), 0);
  }
  
  // generate another player level of the tree
  // FIXME: should we use the list c++ structure?
  Node *successors = moveGen(position, player);

  if (successors.empty() == 0) {
    return Node(staticEval(position, player), 0);
  }
  
  int newValue, bestPath;
  for (Node succ : successors) {
    Node result_succ = minimaxAB(succ.value, depth + 1, !player, -(passThresh), -(useThresh));
    newValue = -(result_succ.value);
    if (newValue > passThresh) {
      newValue = passThresh;
      //bestPath = ???;
    }

    if (passThresh >= useThresh) {
      return Node(passThresh, bestPath);
    }
  }

  return Node(passThresh, bestPath);
}

bool deepEnough(int position, int depth) {
  // FIXME: determine what value represents a terminal node for position
  if (depth == 0 /*|| position == terminal node*/) {
    return true;
  }
  return false;
}

/*
  the static evaluation function
  returns: a number respresenting the goodness of position from the standpoint of the player
*/
int staticEval(int position, bool player) {

}

/*
  the plausible-move generator
  returns: a list of nodes representing moves that can be made
*/
Node* moveGen(int position, bool player) {

}
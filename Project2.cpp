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
  vector<Node> path;

  Node(int v, vector<Node> p) {
    value = v;
    path = p; // FIXME; should this be a list? or just point to next node?
  }
};

// function declarations:
Node minimaxAB(int position, int depth, bool player, int useThresh, int passThresh);
bool deepEnough(int position, int depth);
int staticEval(int position, bool player);
vector<Node> moveGen(int position, bool player);
//drawBoard(...);

//TODO: for each group member, define evaluation functions (print tables to a file?)

int main() {
  return 0;
}

// useThresh is worst score for MAX (negative val)
// passThreshh is worst score for MIN (positive val)
Node minimaxAB(int position, int depth, bool player, int useThresh, int passThresh) {
  if (deepEnough(position, depth)) {
    vector<Node> path; // create a null vector to pass to Node struct
    return Node(staticEval(position, player), path);
  }
  
  vector<Node> successors = moveGen(position, player); // generate another level of the tree

  if (successors.empty()) {
    vector<Node> path; // create a null vector to pass to Node struct
    return Node(staticEval(position, player), path);
  }
  
  int newValue;
  vector<Node> bestPath;
  for (Node succ : successors) {
    Node result_succ = minimaxAB(succ.value, depth + 1, !player, -(passThresh), -(useThresh));
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

bool deepEnough(int position, int depth) {
  // FIXME: determine what value represents a terminal node for position
  if (depth == 0 /*|| position == terminal node / game over*/) {
    return true;
  }
  return false;
}

/*
  the static evaluation function, or the "heuristic"
  returns: a number respresenting the goodness of position from the standpoint of the player
*/
int staticEval(int position, bool player) {

}

/*
  the plausible-move generator
  returns: a list of nodes representing moves that can be made
*/
vector<Node> moveGen(int position, bool player) {
  vector<Node> successors;

  return successors;
}
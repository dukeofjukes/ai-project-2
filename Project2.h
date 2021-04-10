#include <string>
#include <iostream>
#include <vector>
#include <tuple>
#include <time.h>
#define COLUMNS 7
#define ROWS 6


struct Node{
    int value, row, col;
    std::vector<Node> path;

    Node(int v, std::vector<Node> p) 
    {
        value = v;
        path = p;
    }
};

class Connect4
{
    public: 
        // function declarations:
        Connect4();
        Node minimaxAB(int row, int col, int depth, bool player, int useThresh, int passThresh);
        bool deepEnough(int row, int col, int depth);
        std::vector<Node> moveGen(int row, int col, bool player);
        void drawBoard();
        void playGame();
        void initializeBoard();
        void updateBoard(Node move);
        char getPiece(int slot);

        //TODO: for each group member, define evaluation functions (print tables to a file?)
        int staticEval(int row, int col, bool player);  


    private:
        int board[COLUMNS][ROWS];

};

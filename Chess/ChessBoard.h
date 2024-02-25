#pragma once
#include <vector>
#include "SFML/Graphics.hpp"
#include <sstream>
#include <cstring>

struct move
{
    int oX, oY, X, Y;
    move() {}
    move(int oldX, int oldY, int newX, int newY);
};
struct board
{
    int arr[8][8] = { 
        {7, 6, -1, -1, -1, -1, 0, 1},
        {8, 6, -1, -1, -1, -1, 0, 2},
        {9, 6, -1, -1, -1, -1, 0, 3},
        {11, 6, -1, -1, -1, -1, 0, 5},
        {10, 6, -1, -1, -1, -1, 0, 4},
        {9, 6, -1, -1, -1, -1, 0, 3},
        {8, 6, -1, -1, -1, -1, 0, 2},
        {7, 6, -1, -1, -1, -1, 0, 1} 
    };
};
class ChessBoard
{
private:
    bool turn = 1;
    const char* notation(int x, int y);
    std::vector<board> history;

    void wPawn(std::vector<move>& moves, int x, int y, board newboard);
    void bPawn(std::vector<move>& moves, int x, int y, board newboard);
    void King(std::vector<move>& moves, int x, int y, board newboard);
    void Queen(std::vector<move>& moves, int x, int y, board newboard);
    void Rook(std::vector<move>& moves, int x, int y, board newboard);
    void Bishop(std::vector<move>& moves, int x, int y, board newboard);
    void Knight(std::vector<move>& moves, int x, int y, board newboard);

    int score(board board);

public:
    std::vector<move> getLegalMoves(board b, bool color);
    board currBoard;
    bool playMove(move req);
    bool playMove(move req , board newboard , bool newturn, std::vector<move> movesthisTurn);
    bool nextTurn();
    bool canwKingQcastle = true;
    bool canwKingKcastle = true;
    bool canbKingKcastle = true;
    bool canbKingQcastle = true;


    sf::Text text;
    std::vector<move> moves;

    bool getTurn() {
        return turn;
    }

    move bestMove(board newboard, bool turn, int depth);

    int score();
};
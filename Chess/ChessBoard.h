#pragma once
#include <vector>
#include "SFML/Graphics.hpp"
#include <sstream>
#include <cstring>
#include <map>

struct Position {
    int X, Y;
};

struct move
{
    Position oldPos, newPos;
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
    
    float score = 0;

    short whitePiecesLeft = 16;
    short blackPiecesLeft = 16;

    void updateScore(float a) {
        score -= a;
    }
};
class ChessBoard
{
private:
    bool turn = 1;
    std::vector<board> history;
    int Depth = 7;

    void wPawn(std::vector<move>& moves, int x, int y, board newboard);
    void bPawn(std::vector<move>& moves, int x, int y, board newboard);
    void King(std::vector<move>& moves, int x, int y, board newboard);
    void Queen(std::vector<move>& moves, int x, int y, board newboard);
    void Rook(std::vector<move>& moves, int x, int y, board newboard);
    void Bishop(std::vector<move>& moves, int x, int y, board newboard);
    void Knight(std::vector<move>& moves, int x, int y, board newboard);

    void executeMove(board& gameBoard, const move& req);
    void undoMove(board& gameBoard, const move& req, int capturedPiece);
    void handleSpecialMoves(board& gameBoard, const move& req);
    bool isMoveValid(const move& legalMove, const move& req);

public:
    ChessBoard();

    std::vector<move> getLegalMoves(board b, bool color);
    board currBoard;
    bool playMove(move req);
    bool playMoveAI(move req , board newboard , bool newturn, const std::vector<move> movesthisTurn );
    bool nextTurn();
    bool canwKingQcastle = true;
    bool canwKingKcastle = true;
    bool canbKingKcastle = true;
    bool canbKingQcastle = true;

    void setDepth(int indepth) {
        Depth = indepth;
    }

    sf::Text text;
    std::vector<move> moves;

    int counter = 0;

    bool getTurn() {
        return turn;
    }

    std::map<int, int> pieceScores; // represents the score of piece based on thier ability
    std::map<int, std::vector<std::vector<float>>> piecePosScores; // represents the score of piece based on thier positional advantage, this can be altered to change the behaviour of AI

    bool isInCheck(board newboard, bool newTurn);

    float score(move m, const board newboard);
    board createnewboard(move m, board& currgoingboard);

    void quicksort(std::vector<move>& vec, int L, int R, board newboard, bool newturn);
};
#pragma once
#include <vector>
#include "SFML/Graphics.hpp"
#include <sstream>
#include <cstring>
#include <map>

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
    //buggy algo for this
    /*int arr[8][8] = {
        {7, -1, 6, -1, -1, -1, 0, 1},
        {8, -1, -1, 6, -1, 3, 0, 2},
        {9, 6, -1, -1, -1, -1, 0, 3},
        {11, 6, -1, -1, -1, -1, 0, 5},
        {10, 6, -1, -1, 0, -1, -1, 4},
        {9, 6, -1, -1, -1, -1, 0, -1},
        {8, 6, -1, -1, -1, -1, 0, 2},
        {7, -1, -1, 6, -1, -1, 0, 1}
    };*/
    float score = 0;

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

    float MinMaxRecursion(board newboard, bool newturn,int depth ,bool* Checkmate,move &RecursionBestMove);
    float NegaMaxRecursion(board newboard, bool newturn, int depth, bool* Checkmate, move& RecursionBestMove);
    float NegaMaxRecursionAlphaBeta(board newboard, bool newturn, int depth, bool* Checkmate,float alpha , float beta, move& RecursionBestMove);
    void sortMoves(std::vector<move>& movesThisTurn, board newboard,bool newTurn);

public:
    ChessBoard();

    std::vector<move> getLegalMoves(board b, bool color);
    board currBoard;
    bool playMove(move req);
    bool playMoveAI(move req , board newboard , bool newturn, std::vector<move> movesthisTurn );
    bool nextTurn();
    bool canwKingQcastle = true;
    bool canwKingKcastle = true;
    bool canbKingKcastle = true;
    bool canbKingQcastle = true;

    sf::Text text;
    std::vector<move> moves;

    int counter = 0;

    bool getTurn() {
        return turn;
    }

    std::map<int, int> pieceScores;
    std::map<int, std::vector<std::vector<float>>> piecePosScores;


    move bestMove(board newboard, bool turn, int depth,bool *Checkmate, bool* isMeCheckmate);
    move MinMax(board newboard, bool newturn, bool* Checkmate);
    move MinMaxRecursionhelper(board newboard, bool newturn, bool* Checkmate);
    move NegaMaxRecursionhelper(board newboard, bool newturn, bool* Checkmate);

    float score(move m, const board newboard);
    board createnewboard(move m, board& currgoingboard);

    void quicksort(std::vector<move>& vec, int L, int R, board newboard, bool newturn);
};
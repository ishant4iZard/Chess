#pragma once
#include <vector>

class ChessBoard;
class board;
struct move;

class ChessAI
{
public:

    move bestMove(board newboard, bool turn, int depth, bool* Checkmate, bool* isMeCheckmate);
    move MinMax(board newboard, bool newturn, bool* Checkmate);
    move MinMaxRecursionhelper(board newboard, bool newturn, bool* Checkmate);
    move NegaMaxRecursionhelper(board newboard, bool newturn, bool* Checkmate, bool* Stalemate, int depth = 7);

    void setDepth(int indepth) {
        Depth = indepth;
    }

    ChessBoard* playboard;
    
    ChessAI(ChessBoard& inplayboard) {
        playboard = &inplayboard;
    }

private:

    float MinMaxRecursion(board newboard, bool newturn, int depth, bool* Checkmate, move& RecursionBestMove);
    float NegaMaxRecursion(board newboard, bool newturn, int depth, bool* Checkmate, move& RecursionBestMove);
    float NegaMaxRecursionAlphaBeta(board newboard, bool newturn, int depth, bool* Checkmate, bool* Stalemate, float alpha, float beta, move& RecursionBestMove);
    float NegaMaxRecursionAlphaBetaThreads(board newboard, bool newturn, int depth, bool* Checkmate, bool* Stalemate, float alpha, float beta, move& RecursionBestMove);
    void sortMoves(std::vector<move>& movesThisTurn, board newboard, bool newTurn);

    int Depth = 7;

};
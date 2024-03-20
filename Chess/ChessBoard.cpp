#include <vector>
#include <thread>
#include <iostream>
#include <functional>
#include <mutex>
#include "chessBoard.h"
#include "ChessAI.h"
#include "piecePositionScores.h"


move::move(int oldX, int oldY, int newX, int newY)
{
    oldPos.X = oldX;
    oldPos.Y = oldY;
    newPos.X = newX;
    newPos.Y = newY;
}

float ChessBoard::score(move m, const board newboard) {
    if (m.newPos.X == -1) {
        return 0;
    }
    int pieceCaptured = newboard.arr[m.newPos.X][m.newPos.Y], 
        pieceMoved = newboard.arr[m.oldPos.X][m.oldPos.Y], 
        scoreCaptured = 0;
    float positionScoreCaptured = 0, newpositionScore = 0 , oldPositionScore = 0;

    int turnMultiplier = pieceMoved < 6 ? -1 : 1;//update score subtracts score

    if (pieceCaptured != -1) {
        scoreCaptured = pieceScores[pieceCaptured];
        positionScoreCaptured = turnMultiplier * piecePosScores[pieceCaptured][m.newPos.X][m.newPos.Y] * 0.1f;
    }
    newpositionScore = turnMultiplier * piecePosScores[pieceMoved][m.newPos.X][m.newPos.Y] * 0.1f;
    oldPositionScore = turnMultiplier * piecePosScores[pieceMoved][m.oldPos.X][m.oldPos.Y] * 0.1f;

    return scoreCaptured + positionScoreCaptured + newpositionScore - oldPositionScore;

}

ChessBoard::ChessBoard()
{
    pieceScores[0] = 1;
    pieceScores[1] = 5;
    pieceScores[2] = 3;
    pieceScores[3] = 3;
    pieceScores[4] = 999;
    pieceScores[5] = 9;
    pieceScores[6] = -1;
    pieceScores[7] = -5;
    pieceScores[8] = -3;
    pieceScores[9] = -3;
    pieceScores[10] = -999;
    pieceScores[11] = -9;
    pieceScores[-1] = 0;

    //piecePosScores[0] = KnightScores;
    piecePosScores[0] = WhitePawnScores;
    piecePosScores[1] = KnightScores;
    piecePosScores[2] = KnightScores;
    piecePosScores[3] = BishopScores;
    piecePosScores[4] = BishopScores;
    piecePosScores[5] = BishopScores;
    piecePosScores[6] = BlackPawnScores;
    piecePosScores[7] = KnightScores;
    piecePosScores[8] = KnightScores;
    piecePosScores[9] = BishopScores;
    piecePosScores[10] = BishopScores;
    piecePosScores[11] = BishopScores;
    piecePosScores[-1] = KnightScores;

    ChessBoard::turn = 1;

    canwKingQcastle = true;
    canwKingKcastle = true;
    canbKingKcastle = true;
    canbKingQcastle = true;
}

bool ChessBoard::playMove(move req) {
    moves = getLegalMoves(currBoard, turn);

    for (const auto& tempMove : moves) {
        if (isMoveValid(tempMove, req)) {
            int capturedPiece = currBoard.arr[req.newPos.X][req.newPos.Y];
            float moveScore = score(req, currBoard);

            executeMove(currBoard, req);
            handleSpecialMoves(currBoard, req);

            if (isInCheck(currBoard, turn)) {
                undoMove(currBoard, req, capturedPiece);
            }
            else {
                history.push_back(currBoard);
                currBoard.updateScore(moveScore);
                std::cout << currBoard.score << "\n";
                return true;
            }
        }
    }
    std::cout << currBoard.score << "\n";
    return false;
}

bool ChessBoard::playMoveAI(move req, board newboard, bool newturn, const std::vector<move> movesthisTurn)
{
    for (const auto& tempMove : movesthisTurn) {
        if (isMoveValid(tempMove, req)) {
            int capturedPiece = newboard.arr[req.newPos.X][req.newPos.Y];

            executeMove(newboard, req);
            handleSpecialMoves(newboard, req);

            if (isInCheck(newboard, newturn)) {
                undoMove(newboard, req, capturedPiece);
            }
            else {
                undoMove(newboard, req, capturedPiece);
                return true;
            }
        }
    }
    return false;
}

board ChessBoard::createnewboard(move m , board& currgoingboard) {
    board ans = currgoingboard;
    float tempPoints = score(m,currgoingboard);
    executeMove(ans, m);
    handleSpecialMoves(ans, m);

    ans.updateScore(tempPoints);
    return ans;
}

bool ChessBoard::isInCheck(board newboard, bool newTurn)
{
    std::vector<move> tempMoves = getLegalMoves(newboard, !newTurn);
    for (int j = 0; j < tempMoves.size(); ++j)
    {
        int piece = newboard.arr[tempMoves[j].newPos.X][tempMoves[j].newPos.Y];
        if (newboard.arr[tempMoves[j].newPos.X][tempMoves[j].newPos.Y] == 4 || newboard.arr[tempMoves[j].newPos.X][tempMoves[j].newPos.Y] == 10)
        {
            return true;
        }
    }
    return false;
}



void ChessBoard::quicksort(std::vector<move>& vec, int L, int R, board newboard, bool newturn) {
    int turnMultiplier = newturn ? 1 : -1;
    int i, j, mid;
    float piv;
    i = L;
    j = R;
    mid = L + (R - L) / 2;
    piv = turnMultiplier * (createnewboard(vec[mid], newboard)).score;

    while (i<R || j>L) {
        while (turnMultiplier * createnewboard(vec[i], newboard).score > piv)
            i++;
        while (turnMultiplier * createnewboard(vec[j], newboard).score < piv)
            j--;

        if (i <= j) {
            std::swap(vec[i], vec[j]);
            i++;
            j--;
        }
        else {
            if (i < R)
                quicksort(vec, i, R,newboard,newturn);
            if (j > L)
                quicksort(vec, L, j,newboard,newturn);
            return;
        }
    }
}

void ChessBoard::executeMove(board& gameBoard, const move& req)
{
    gameBoard.arr[req.newPos.X][req.newPos.Y] = gameBoard.arr[req.oldPos.X][req.oldPos.Y];
    gameBoard.arr[req.oldPos.X][req.oldPos.Y] = -1;
}

void ChessBoard::undoMove(board& gameBoard, const move& req, int capturedPiece)
{
    gameBoard.arr[req.oldPos.X][req.oldPos.Y] = gameBoard.arr[req.newPos.X][req.newPos.Y];
    gameBoard.arr[req.newPos.X][req.newPos.Y] = capturedPiece;
}

void ChessBoard::handleSpecialMoves(board& gameBoard, const move& req)
{
    int piece = gameBoard.arr[req.newPos.X][req.newPos.Y];

    if (piece == 4 && req.newPos.X - req.oldPos.X == 2) { // White King-side castling
        gameBoard.arr[5][7] = 1;
        gameBoard.arr[7][7] = -1;
    }
    else if (piece == 4 && req.oldPos.X - req.newPos.X == 2) { // White Queen-side castling
        gameBoard.arr[3][7] = 1;
        gameBoard.arr[0][7] = -1;
    }
    else if (piece == 10 && req.newPos.X - req.oldPos.X == 2) { // Black King-side castling
        gameBoard.arr[5][0] = 7;
        gameBoard.arr[7][0] = -1;
    }
    else if (piece == 10 && req.oldPos.X - req.newPos.X == 2) { // Black Queen-side castling
        gameBoard.arr[3][0] = 7;
        gameBoard.arr[0][0] = -1;
    }
    else if (piece == 0 && req.newPos.Y == 0) { // White pawn promotion
        gameBoard.arr[req.newPos.X][req.newPos.Y] = 5; //currently can only promote to queen
    }
    else if (piece == 6 && req.newPos.Y == 7) { // Black pawn promotion
        gameBoard.arr[req.newPos.X][req.newPos.Y] = 11; //currently can only promote to queen
    }
}

bool ChessBoard::isMoveValid(const move& legalMove, const move& req) {
    return (legalMove.oldPos.X == req.oldPos.X && legalMove.oldPos.Y == req.oldPos.Y &&
        legalMove.newPos.X == req.newPos.X && legalMove.newPos.Y == req.newPos.Y);
}

bool ChessBoard::nextTurn()
{
    turn = !turn;
    return turn;
}
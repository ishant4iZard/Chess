#include <vector>
#include <thread>
#include <iostream>
#include <functional>
#include <mutex>
#include "chessBoard.h"


move::move(int oldX, int oldY, int newX, int newY)
{
    oX = oldX;
    oY = oldY;
    X = newX;
    Y = newY;
}



#pragma region positionScores



std::vector<std::vector<float>> KnightScores =
{
    {1.0f,1.0f,1.0f,1.0f,1.0f,1.0f,1.0f,1.0f},
    {1.0f,2.0f,2.0f,2.0f,2.0f,2.0f,2.0f,1.0f},
    {1.0f,2.0f,3.0f,3.0f,3.0f,3.0f,2.0f,1.0f},
    {1.0f,2.0f,3.0f,4.0f,4.0f,3.0f,2.0f,1.0f},
    {1.0f,2.0f,3.0f,4.0f,4.0f,3.0f,2.0f,1.0f},
    {1.0f,2.0f,3.0f,3.0f,3.0f,3.0f,2.0f,1.0f},
    {1.0f,2.0f,2.0f,2.0f,2.0f,2.0f,2.0f,1.0f},
    {1.0f,1.0f,1.0f,1.0f,1.0f,1.0f,1.0f,1.0f}
};

std::vector<std::vector<float>> BishopScores =
{
    {4.0f,3.0f,2.0f,1.0f,1.0f,2.0f,3.0f,4.0f},
    {3.0f,4.1f,3.1f,2.1f,2.1f,3.1f,4.1f,3.0f},
    {2.0f,3.1f,4.2f,3.2f,3.2f,4.2f,3.1f,2.0f},
    {1.0f,2.1f,3.2f,4.3f,4.3f,3.2f,2.1f,1.0f},
    {1.0f,2.1f,3.2f,4.3f,4.3f,3.2f,2.1f,1.0f},
    {2.0f,3.1f,4.2f,3.3f,3.3f,4.2f,3.1f,2.0f},
    {3.0f,4.1f,3.1f,2.1f,2.1f,3.1f,4.1f,3.0f},
    {4.0f,3.0f,1.0f,1.0f,1.0f,1.0f,3.0f,4.0f}
};

std::vector<std::vector<float>> WhitePawnScores =
{
    {10.0f,8.0f,4.5f,4.2f,4.0f,2.0f,1.0f,0.0f},
    {10.0f,8.1f,4.5f,4.2f,4.0f,2.0f,1.0f,0.0f},
    {10.0f,8.1f,4.5f,4.2f,4.0f,2.0f,1.0f,0.0f},
    {10.0f,8.1f,4.5f,4.5f,4.2f,2.0f,0.0f,0.0f},
    {10.0f,8.1f,4.5f,4.5f,4.2f,2.0f,0.0f,0.0f},
    {10.0f,8.1f,4.5f,4.2f,4.0f,2.0f,1.0f,0.0f},
    {10.0f,8.1f,4.5f,4.2f,4.0f,2.0f,1.0f,0.0f},
    {10.0f,8.0f,4.5f,4.2f,4.0f,2.0f,1.0f,0.0f}
};

std::vector<std::vector<float>> BlackPawnScores =
{
    {0.0f,1.0f,2.0f,4.0f,4.2f,4.5f,8.0f,10.0f},
    {0.0f,1.0f,2.0f,4.0f,4.2f,4.5f,8.1f,10.0f},
    {0.0f,1.0f,2.0f,4.0f,4.2f,4.5f,8.1f,10.0f},
    {0.0f,0.0f,2.0f,4.2f,4.5f,4.5f,8.1f,10.0f},
    {0.0f,0.0f,2.0f,4.2f,4.5f,4.5f,8.1f,10.0f},
    {0.0f,1.0f,2.0f,4.0f,4.2f,4.5f,8.1f,10.0f},
    {0.0f,1.0f,2.0f,4.0f,4.2f,4.5f,8.1f,10.0f},
    {0.0f,1.0f,2.0f,4.0f,4.2f,4.5f,8.0f,10.0f}
};



#pragma endregion

float ChessBoard::score(move m, const board newboard) {
    if (m.X == -1) {
        return 0;
    }
    int pieceCaptured = newboard.arr[m.X][m.Y], pieceMoved = 0, scoreCaptured = 0;
    float positionScoreCaptured = 0, newpositionScore = 0 , oldPositionScore = 0;
    pieceMoved = newboard.arr[m.oX][m.oY];

    int turnMultiplier = pieceMoved < 6 ? -1 : 1;//update score subtracts score

    if (pieceCaptured != -1) {

        scoreCaptured = pieceScores[pieceCaptured];
        positionScoreCaptured = turnMultiplier * piecePosScores[pieceCaptured][m.X][m.Y] * 0.1f;
    }
    newpositionScore = turnMultiplier * piecePosScores[pieceMoved][m.X][m.Y] * 0.1f;
    oldPositionScore = turnMultiplier * piecePosScores[pieceMoved][m.oX][m.oY] * 0.1f;

    float newscore = scoreCaptured + positionScoreCaptured + newpositionScore - oldPositionScore;

    //return scoreCaptured + positionScoreCaptured + newpositionScore - oldPositionScore;
    return newscore;
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
    piecePosScores[4] = KnightScores;
    piecePosScores[5] = KnightScores;
    piecePosScores[6] = BlackPawnScores;
    piecePosScores[7] = KnightScores;
    piecePosScores[8] = KnightScores;
    piecePosScores[9] = BishopScores;
    piecePosScores[10] = KnightScores;
    piecePosScores[11] = KnightScores;
    piecePosScores[-1] = KnightScores;
}

bool ChessBoard::playMove(move req)
{
    moves = getLegalMoves(currBoard, turn);

    move temp;
    bool check = false;
    for (int i = 0; i < moves.size(); ++i)
    {
        temp = moves[i];
        if (temp.oX == req.oX && temp.oY == req.oY && temp.X == req.X && temp.Y == req.Y && !check)
        {
            int tempm = currBoard.arr[req.X][req.Y];
            float tempms = score(req,currBoard);
            currBoard.arr[req.X][req.Y] = currBoard.arr[req.oX][req.oY];
            currBoard.arr[req.oX][req.oY] = -1;
            if (currBoard.arr[req.X][req.Y] == 4 && req.X - req.oX == 2) {
                currBoard.arr[5][7] = 1;
                currBoard.arr[7][7] = -1;
            }
            if (currBoard.arr[req.X][req.Y] == 4 && req.oX - req.X == 2) {
                currBoard.arr[3][7] = 1;
                currBoard.arr[0][7] = -1;
            }
            if (currBoard.arr[req.X][req.Y] == 10 && req.X - req.oX == 2) {
                currBoard.arr[5][0] = 7;
                currBoard.arr[7][0] = -1;
            }
            if (currBoard.arr[req.X][req.Y] == 10 && req.X - req.oX == 2) {
                currBoard.arr[3][0] = 7;
                currBoard.arr[0][0] = -1;
            }
            if (currBoard.arr[req.X][req.Y] == 0 && req.Y == 0) {
                currBoard.arr[req.X][req.Y] = 5;
                tempms = -9;
            }
            if (currBoard.arr[req.X][req.Y] == 6 && req.Y == 7) {
                currBoard.arr[req.X][req.Y] = 11;
                tempms = 9;
            }
            if(isInCheck(currBoard,turn))
                currBoard = history[history.size() - 1];

            else
            {
                /*if (currBoard.arr[req.X][req.Y] == 4) {
                    canwKingKcastle = false;
                    canwKingQcastle = false;
                }if (currBoard.arr[req.X][req.Y] == 10) {
                    canwKingKcastle = false;
                    canwKingQcastle = false;
                }*/
                history.push_back(currBoard);
                currBoard.updateScore(tempms);
                std::cout << currBoard.score;

                return true;
            }
        }
    }
    std::cout << currBoard.score;
    return false;
}

bool ChessBoard::playMoveAI(move req , board newboard , bool newturn , std::vector<move> movesthisTurn)
{
    move temp;
    bool check = false;
    for (int i = 0; i < movesthisTurn.size(); ++i)
    {
        temp = movesthisTurn[i];
        if (temp.oX == req.oX && temp.oY == req.oY && temp.X == req.X && temp.Y == req.Y && !check)
        {
            int tempm = newboard.arr[req.X][req.Y];
            newboard.arr[req.X][req.Y] = newboard.arr[req.oX][req.oY];
            newboard.arr[req.oX][req.oY] = -1;
            if (newboard.arr[req.X][req.Y] == 4 && req.X - req.oX == 2) {
                newboard.arr[5][7] = 1;
                newboard.arr[7][7] = -1;
            }   
            if (newboard.arr[req.X][req.Y] == 4 && req.oX - req.X == 2) {
                newboard.arr[3][7] = 1;
                newboard.arr[0][7] = -1;
            }   
            if (newboard.arr[req.X][req.Y] == 10 && req.X - req.oX == 2) {
                newboard.arr[5][0] = 7;
                newboard.arr[7][0] = -1;
            }   
            if (newboard.arr[req.X][req.Y] == 10 && req.X - req.oX == 2) {
                newboard.arr[3][0] = 7;
                newboard.arr[0][0] = -1;
            }
            if (newboard.arr[req.X][req.Y] == 0 && req.Y == 0) {
                newboard.arr[req.X][req.Y] = 5;
            }
            if (newboard.arr[req.X][req.Y] == 6 && req.Y == 7) {
                newboard.arr[req.X][req.Y] = 11;
            }
            if (isInCheck(newboard, newturn)) {
                newboard.arr[req.oX][req.oY] = newboard.arr[req.X][req.Y];
                newboard.arr[req.X][req.Y] = tempm;
            }
            else{
                newboard.arr[req.oX][req.oY] = newboard.arr[req.X][req.Y];
                newboard.arr[req.X][req.Y] = tempm;
                return true;
            }

        }
    }
    return false;
}


board ChessBoard::createnewboard(move m , board& currgoingboard) {
    board ans = currgoingboard;
    float tempPoints = score(m,currgoingboard);
    ans.arr[m.X][m.Y] = ans.arr[m.oX][m.oY];
    ans.arr[m.oX][m.oY] = -1;
    if (ans.arr[m.X][m.Y] == 4 && m.X - m.oX == 2) {
        ans.arr[5][7] = 1;
        ans.arr[7][7] = -1;
    }
    if (ans.arr[m.X][m.Y] == 4 && m.oX - m.X == 2) {
        ans.arr[3][7] = 1;
        ans.arr[0][7] = -1;
    }
    if (ans.arr[m.X][m.Y] == 10 && m.X - m.oX == 2) {
        ans.arr[5][0] = 7;
        ans.arr[7][0] = -1;
    }
    if (ans.arr[m.X][m.Y] == 10 && m.X - m.oX == 2) {
        ans.arr[3][0] = 7;
        ans.arr[0][0] = -1;
    }
    if (ans.arr[m.X][m.Y] == 0 && m.Y == 0) {
        ans.arr[m.X][m.Y] = 5;
        tempPoints -= 9;
    }
    if (ans.arr[m.X][m.Y] == 6 && m.Y == 7) {
        ans.arr[m.X][m.Y] = 11;
        tempPoints += 9;
    }
    ans.updateScore(tempPoints);
    return ans;
}

bool ChessBoard::isInCheck(board newboard, bool newTurn)
{
    bool check = false;
    std::vector<move> tempMoves = getLegalMoves(newboard, !newTurn);
    for (int j = 0; j < tempMoves.size(); ++j)
    {
        if (newboard.arr[tempMoves[j].X][tempMoves[j].Y] == 4 || newboard.arr[tempMoves[j].X][tempMoves[j].Y] == 10)
        {
            check = true;
            /*newboard.arr[req.oX][req.oY] = newboard.arr[req.X][req.Y];
            newboard.arr[req.X][req.Y] = tempm;*/

            break;
        }
    }
    return check;
}

move ChessBoard::bestMove(board newboard,bool newturn, int depth,bool* Checkmate , bool* isMeCheckmate) {
    std::vector<move> Movesthisturn = getLegalMoves(newboard, newturn);
    int itr = 0;
    if (depth == 0) {
        move m (-1,-1,-1,-1);
        while (itr<Movesthisturn.size())
        {
            if (playMoveAI(Movesthisturn[itr], newboard , newturn, Movesthisturn)) {
                m = Movesthisturn[itr];
                break;
            }
            itr++;
        }
        return m;
    }

    std::vector<move> BestMoves;
    std::vector<move> ForcedMoves;
    move BestMove;
    int oldScore = newturn == 1 ? (-999) : (999);


    for (int i = 0; i < Movesthisturn.size(); ++i)
    {
        if (playMoveAI(Movesthisturn[i], newboard, newturn, Movesthisturn)) {
            board recursionBoard = createnewboard(Movesthisturn[i], newboard);
            bool checkmate = false;
            bool ismecheckmate = false;
            move bestOpponentMove = bestMove(recursionBoard, !newturn, depth - 1, &checkmate , &ismecheckmate);
            if (checkmate) {
                *isMeCheckmate = true;
                return Movesthisturn[i];
            }
            if (ismecheckmate) {
                ForcedMoves.push_back(Movesthisturn[i]);
                continue;
            }
            board bestOpponentBoard = createnewboard(bestOpponentMove, recursionBoard);
            int newScore = bestOpponentBoard.score;
            if ((newturn == 1 && (newScore > oldScore)) || (newturn == 0 && (oldScore > newScore))) {
                BestMoves.clear();
                BestMove = Movesthisturn[i];
                BestMoves.push_back(BestMove);
                oldScore = newScore;
            }
            if (oldScore == newScore) {
                BestMove = Movesthisturn[i];
                BestMoves.push_back(BestMove);
            }
        }
        else {
            Movesthisturn.erase(Movesthisturn.begin() + i);
            i--;
        }
    }
    if (Movesthisturn.size() == 0) {
        *Checkmate = true;
    }
    if (BestMoves.size()!=0) {
        int random = (rand() * rand() % BestMoves.size());
        BestMove = BestMoves[random];
    }
    else {
        if (ForcedMoves.size() != 0) {
            int random = (rand() * rand() % ForcedMoves.size());
            BestMove = ForcedMoves[random];
        }
    }
    return BestMove;
}

move ChessBoard::MinMax(board newboard, bool newturn, bool* Checkmate) {
    int TurnMultipler = newturn ? 1 : -1;
    int opponentMinMaxScore = 999;
    move bestMove(-1, -1, -1, -1);
    std::vector<move> Movesthisturn = getLegalMoves(newboard, newturn);
    std::vector<move> BestMoves;
    std::vector<move> ForcedMoves;

    for (auto mymoves : Movesthisturn) {
        int opponentMaxScore = INT_MIN;
        int score;
        if (playMoveAI(mymoves, newboard, newturn, Movesthisturn)) {
            board recursionBoard = createnewboard(mymoves, newboard);
            std::vector<move> OpponentMovesthisTurn = getLegalMoves(recursionBoard, !newturn);
            std::vector<move> BestOpponentMoves;
            std::vector<move> ForcedOpponentMoves;

            for (auto opponentmove : OpponentMovesthisTurn) {
                if (playMoveAI(opponentmove, recursionBoard, !newturn, OpponentMovesthisTurn)) {
                    board OpponentrecursionBoard = createnewboard(opponentmove, recursionBoard);
                    score = -TurnMultipler * OpponentrecursionBoard.score;
                    if (score > opponentMaxScore) {
                        opponentMaxScore = score;
                        BestOpponentMoves.clear();
                        BestOpponentMoves.push_back(opponentmove);
                    }
                    else if (score == opponentMaxScore) {
                        BestOpponentMoves.push_back(opponentmove);
                    }
                }
            }
            if (BestOpponentMoves.size() == 0) {
                return mymoves;
            }
            if (opponentMaxScore < opponentMinMaxScore) {
                opponentMinMaxScore = opponentMaxScore;
                BestMoves.clear();
                BestMoves.push_back(mymoves);
            }
            else if (opponentMaxScore == opponentMinMaxScore) {
                BestMoves.push_back(mymoves);
            }
        }
    }
    if (BestMoves.size() == 0) {
        *Checkmate = true;
    }
    else {
        int random = (rand() * rand() % BestMoves.size());
        bestMove = BestMoves[random];
    }
    return bestMove;
}




float ChessBoard::MinMaxRecursion(board newboard, bool newturn, int depth ,bool* Checkmate, move& RecursionBestMove)
{
    if (depth == 0) {
        return newboard.score;
    }
    std::vector<move> Movesthisturn = getLegalMoves(newboard, newturn);
    std::vector<move> BestMoves;
    std::vector<move> ForcedMoves;

    float score;

    if (newturn) {
        float maxscore = -999;
        for (auto mymoves : Movesthisturn) {
            counter++;
            if (playMoveAI(mymoves, newboard, newturn, Movesthisturn)) {
                board myBoard = createnewboard(mymoves, newboard);
                bool checkmate;
                score = MinMaxRecursion(myBoard, false, depth - 1, &checkmate, RecursionBestMove);
                if (score > maxscore) {
                    maxscore = score;
                    BestMoves.clear();
                    BestMoves.push_back(mymoves);
                }
                else if (score == maxscore && depth == Depth) {
                    BestMoves.push_back(mymoves);
                }
            }
        }
        if (depth == Depth) {
            if (BestMoves.size() == 0) {
                *Checkmate = true;
            }
            if(BestMoves.size()) {
                int random = (rand() * rand() % BestMoves.size());
                RecursionBestMove = BestMoves[random];
            }
        }
        return maxscore;
    }
    else {
        float minscore = 999;
        for (auto mymoves : Movesthisturn) {
            if (playMoveAI(mymoves, newboard, newturn, Movesthisturn)) {
                counter++;
                board myBoard = createnewboard(mymoves, newboard);
                bool checkmate;
                score = MinMaxRecursion(myBoard, true, depth - 1, &checkmate, RecursionBestMove);
                if (score < minscore) {
                    minscore = score;
                    BestMoves.clear();
                    BestMoves.push_back(mymoves);
                }
                else if (score == minscore && depth == Depth) {
                    BestMoves.push_back(mymoves);
                }
            }
        }
        if (depth == Depth) {
            if (BestMoves.size() == 0) {
                *Checkmate = true;
            }
            if (BestMoves.size()) {
                int random = (rand() * rand() % BestMoves.size());
                RecursionBestMove = BestMoves[random];
            }
        }
        return minscore;
    }   
}

move ChessBoard::MinMaxRecursionhelper(board newboard, bool newturn, bool* Checkmate)
{
    move RecursionBestMove(-1,-1,-1,-1);
    MinMaxRecursion(newboard, newturn,Depth ,Checkmate, RecursionBestMove);
    return RecursionBestMove;
}

float ChessBoard::NegaMaxRecursion(board newboard, bool newturn, int depth, bool* Checkmate, move& RecursionBestMove)
{
    int turnMultiplier = newturn ? 1 : -1;
    if (depth == 0) {
        return turnMultiplier * newboard.score;
    }
    std::vector<move> Movesthisturn = getLegalMoves(newboard, newturn);
    std::vector<move> BestMoves;
    std::vector<move> ForcedMoves;

    float score;

    float maxscore = -999;
    for (auto mymoves : Movesthisturn) {
        if (playMoveAI(mymoves, newboard, newturn, Movesthisturn)) {
            counter++;

            board myBoard = createnewboard(mymoves, newboard);
            bool checkmate;
            score = -NegaMaxRecursion(myBoard, !newturn, depth - 1, &checkmate, RecursionBestMove);
            if (score > maxscore) {
                maxscore = score;
                BestMoves.clear();
                BestMoves.push_back(mymoves);
            }
            else if (score == maxscore && depth == Depth) {
                BestMoves.push_back(mymoves);
            }
        }
    }
    if (depth == Depth) {
        if (BestMoves.size() == 0) {
            *Checkmate = true;
        }
        else {
            int random = (rand() * rand() % BestMoves.size());
            RecursionBestMove = BestMoves[random];
        }
    }
    return maxscore;
}

void swap(std::vector<move>& v, int x, int y) {
    move temp = v[x];
    v[x] = v[y];
    v[y] = temp;
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
            swap(vec, i, j);
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


void ChessBoard::sortMoves(std::vector<move>& movesThisTurn, board newboard, bool newTurn) {
    quicksort(movesThisTurn, 0, movesThisTurn.size() - 1, newboard, newTurn);
}



float ChessBoard::NegaMaxRecursionAlphaBeta(board newboard, bool newturn, int depth, bool* Checkmate,bool* Stalemate ,float alpha, float beta, move& RecursionBestMove) {
    int turnMultiplier = newturn ? 1 : -1;
    if (depth >= Depth) {
        return turnMultiplier * newboard.score;
    }
    std::vector<move> Movesthisturn = getLegalMoves(newboard, newturn);

    std::vector<move> BestMoves;

    float score;
    int invalidMovesCounter = 0;

    /*if (Movesthisturn.size() < 30) {
        Depth = 10;
    }
    else {
        Depth = 7;
    }*/

    float maxscore = -999;

    sortMoves(Movesthisturn, newboard, newturn);

    for (auto mymoves : Movesthisturn) {
        if (playMoveAI(mymoves, newboard, newturn, Movesthisturn)) {
            counter++;
            board myBoard = createnewboard(mymoves, newboard);
            bool checkmate = false;
            bool stalemate = false;
            score = -NegaMaxRecursionAlphaBeta(myBoard, !newturn, depth + 1, &checkmate,&stalemate ,-beta, -alpha, RecursionBestMove);
            if (stalemate == true) {
                score = -999;
            }
            if (score > maxscore) {
                maxscore = score;
                BestMoves.clear();
                BestMoves.push_back(mymoves);
            }
            else if (score == maxscore && depth == 0 /*&& score!=-999*/) {
                BestMoves.push_back(mymoves);
            }
            if (maxscore > alpha) {
                alpha = maxscore;
            }
            if (alpha >= beta ) {
                break;
            }
        }
        else {
            invalidMovesCounter++;
        }
    }
    if (invalidMovesCounter == Movesthisturn.size() && !isInCheck(newboard, newturn)) {
        *Stalemate = true;
        return 0;
    }
    if (depth == 0) {
        if (BestMoves.size() == 0) {
            *Checkmate = true;
        }
        else {
            int random = (rand() % BestMoves.size());
            RecursionBestMove = BestMoves[random];
        }
    }
    return maxscore;
}


float ChessBoard::NegaMaxRecursionAlphaBetaThreads(board newboard, bool newturn, int depth, bool* Checkmate,bool* Stalemate ,float alpha, float beta, move& RecursionBestMove) {
    int turnMultiplier = newturn ? 1 : -1;
    if (depth >= Depth) {
        return turnMultiplier * newboard.score;
    }

    std::vector<move> Movesthisturn = getLegalMoves(newboard, newturn);
    float maxscore = -999;
    std::vector<move> BestMoves;

    int invalidMovesCounter = 0;

    // Adjust depth dynamically
    /*if (Movesthisturn.size() < 30) {
        Depth = 10;
    }
    else {
        Depth = 7;
    }*/

    sortMoves(Movesthisturn, newboard, newturn);

    std::vector<std::thread> threads;
    std::vector<float> scores(Movesthisturn.size());


    for (size_t i = 0; i < Movesthisturn.size(); ++i) {
        threads.emplace_back([&, i]() {
            float score;
            move mymoves = Movesthisturn[i];
            if (playMoveAI(mymoves, newboard, newturn, Movesthisturn)) {
                counter++;
                board myBoard = createnewboard(mymoves, newboard);
                bool checkmate = false;
                bool stalemate = false;
                score = -NegaMaxRecursionAlphaBeta(myBoard, !newturn, depth + 1, &checkmate, &stalemate, -beta, -alpha, RecursionBestMove);

                if (stalemate == true) {
                    score = -999;
                }
            }
            else {
                score = -999; // Invalid move, give it a low score
                invalidMovesCounter++;
            }
            scores[i] = score;
        });
    }

    for (auto& t : threads) {
        t.join();
    }

    if (invalidMovesCounter == Movesthisturn.size() && Depth - 1 == depth && !isInCheck(newboard,newturn)) {
        *Stalemate = true;
        return 0;
    }

    for (size_t i = 0; i < Movesthisturn.size(); ++i) {
        float score = scores[i];
        if (score > maxscore) {
            maxscore = score;
            BestMoves.clear();
            BestMoves.push_back(Movesthisturn[i]);
        }
        else if (score == maxscore && depth == 0) {
            BestMoves.push_back(Movesthisturn[i]);
        }
        if (maxscore > alpha) {
            if (maxscore > 999) {
                if(depth == Depth)
                    RecursionBestMove = Movesthisturn[i];

                return maxscore;
            }
            alpha = maxscore;
        }
        /*if (alpha >= beta) {
            break;
        }*/
    }

    if (depth == 0) {
        if (BestMoves.size() == 0) {
            *Checkmate = true;
        }
        else {
            int random = (rand() % BestMoves.size());
            RecursionBestMove = BestMoves[random];
        }
    }

    return maxscore;
}

move ChessBoard::NegaMaxRecursionhelper(board newboard, bool newturn, bool* Checkmate, bool *Stalemate, int depth)
{
    Depth = depth;
    move RecursionBestMove(-1, -1, -1, -1);
    float alpha = -999;
    float beta = 999;
    counter = 0;
    //bool staleMate = false;
    NegaMaxRecursionAlphaBetaThreads(newboard, newturn, 0, Checkmate, Stalemate, alpha ,beta ,RecursionBestMove);
    //NegaMaxRecursion(newboard, newturn, Depth, Checkmate,RecursionBestMove);
    //MinMax(newboard, newturn, Checkmate);
    //MinMaxRecursion(newboard, newturn, Depth, Checkmate, RecursionBestMove);


    std::cout << "\n" << counter<<"\n";
    return RecursionBestMove;
}

bool ChessBoard::nextTurn()
{
    turn = !turn;
    return turn;
}
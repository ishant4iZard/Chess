#include <vector>
#include "chessBoard.h"
#include<thread>
#include <iostream>

move::move(int oldX, int oldY, int newX, int newY)
{
    oX = oldX;
    oY = oldY;
    X = newX;
    Y = newY;
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
            int tempms = score(tempm);
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
            std::vector<move> tempMoves = getLegalMoves(currBoard, !turn);
            for (int j = 0; j < tempMoves.size(); ++j)
            {
                if (currBoard.arr[tempMoves[j].X][tempMoves[j].Y] == 4  || currBoard.arr[tempMoves[j].X][tempMoves[j].Y] == 10)
                {
                    currBoard = history[history.size() - 1];
                    check = true;
                    break;
                }
            }

            if (!check)
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
                return true;
            }
        }
    }
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
            std::vector<move> tempMoves = getLegalMoves(newboard, !newturn);
            for (int j = 0; j < tempMoves.size(); ++j)
            {
                if (newboard.arr[tempMoves[j].X][tempMoves[j].Y] == 4 || newboard.arr[tempMoves[j].X][tempMoves[j].Y] == 10)
                {
                    check = true;
                    newboard.arr[req.oX][req.oY] = newboard.arr[req.X][req.Y];
                    newboard.arr[req.X][req.Y] = tempm;
                        
                    break;
                }
            }
            if (!check)
            {
                newboard.arr[req.oX][req.oY] = newboard.arr[req.X][req.Y];
                newboard.arr[req.X][req.Y] = tempm;
                return true;
            }

        }
    }
    return false;
}

int ChessBoard::score(int i) {
    if (i == 0) return 1;
    if (i == 1) return 5;
    if (i == 2) return 3;
    if (i == 3) return 3;
    if (i == 4) return INT_MAX;
    if (i == 5) return 9;
    if (i == 6) return -1;
    if (i == 7) return -5;
    if (i == 8) return -3;
    if (i == 9) return -3;
    if (i == 10) return -INT_MAX;
    if (i == 11) return -9;
    if (i == -1) return 0;
}

board ChessBoard::createnewboard(move m , board& currgoingboard) {
    board ans = currgoingboard;
    int tempPoints = score(ans.arr[m.X % 8][m.Y % 8]);
    ans.arr[m.X%8][m.Y%8] = ans.arr[m.oX%8][m.oY%8];
    ans.arr[m.oX%8][m.oY%8] = -1;
    ans.updateScore(tempPoints);
    return ans;
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
    int oldScore = newturn == 1 ? (-INT_MAX) : (INT_MAX);


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
    int opponentMinMaxScore = INT_MAX;
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




int ChessBoard::MinMaxRecursion(board newboard, bool newturn, int depth ,bool* Checkmate, move& RecursionBestMove)
{
    if (depth == 0) {
        return newboard.score;
    }
    std::vector<move> Movesthisturn = getLegalMoves(newboard, newturn);
    std::vector<move> BestMoves;
    std::vector<move> ForcedMoves;

    int score;

    if (newturn) {
        int maxscore = -INT_MAX;
        for (auto mymoves : Movesthisturn) {
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
        int minscore = INT_MAX;
        for (auto mymoves : Movesthisturn) {
            if (playMoveAI(mymoves, newboard, newturn, Movesthisturn)) {
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

int ChessBoard::NegaMaxRecursion(board newboard, bool newturn, int depth, bool* Checkmate, move& RecursionBestMove)
{
    int turnMultiplier = newturn ? 1 : -1;
    if (depth == 0) {
        return turnMultiplier * newboard.score;
    }
    std::vector<move> Movesthisturn = getLegalMoves(newboard, newturn);
    std::vector<move> BestMoves;
    std::vector<move> ForcedMoves;

    int score;

    int maxscore = -INT_MAX;
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

int ChessBoard::NegaMaxRecursionAlphaBeta(board newboard, bool newturn, int depth, bool* Checkmate, int alpha, int beta, move& RecursionBestMove) {
    int turnMultiplier = newturn ? 1 : -1;
    if (depth == 0) {
        return turnMultiplier * newboard.score;
    }
    std::vector<move> Movesthisturn = getLegalMoves(newboard, newturn);
    std::vector<move> BestMoves;
    std::vector<move> ForcedMoves;

    int score;

    int maxscore = -INT_MAX;
    for (auto mymoves : Movesthisturn) {
        if (playMoveAI(mymoves, newboard, newturn, Movesthisturn)) {
            counter++;
            board myBoard = createnewboard(mymoves, newboard);
            bool checkmate;
            score = -NegaMaxRecursionAlphaBeta(myBoard, !newturn, depth - 1, &checkmate, -beta, -alpha, RecursionBestMove);
            if (score > maxscore) {
                maxscore = score;
                BestMoves.clear();
                BestMoves.push_back(mymoves);
            }
            else if (score == maxscore && depth == Depth) {
                BestMoves.push_back(mymoves);
            }
            if (maxscore > alpha) {
                alpha = maxscore;
            }
            if (alpha >= beta) {
                break;
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


move ChessBoard::NegaMaxRecursionhelper(board newboard, bool newturn, bool* Checkmate)
{
    move RecursionBestMove(-1, -1, -1, -1);
    int alpha = -INT_MAX;
    int beta = INT_MAX;
    NegaMaxRecursionAlphaBeta (newboard, newturn, Depth, Checkmate,alpha ,beta ,RecursionBestMove);
    //NegaMaxRecursion(newboard, newturn, Depth, Checkmate,RecursionBestMove);

    std::cout << counter<<"\n";
    return RecursionBestMove;
}

bool ChessBoard::nextTurn()
{
    turn = !turn;
    return turn;
}
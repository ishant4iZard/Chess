#include <vector>
#include "chessBoard.h"
#include<thread>

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

bool ChessBoard::playMoveAI(move req , board newboard , bool newturn , std::vector<move> movesthisTurn, bool* Checkmate)
{
    move temp;
    bool check = false;
    for (int i = 0; i < movesthisTurn.size(); ++i)
    {
        temp = movesthisTurn[i];
        if (temp.oX == req.oX && temp.oY == req.oY && temp.X == req.X && temp.Y == req.Y && !check)
        {
            int tempm = newboard.arr[req.X][req.Y];
            int tempms = score(tempm);
            newboard.arr[req.X][req.Y] = newboard.arr[req.oX][req.oY];
            newboard.arr[req.oX][req.oY] = -1;
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
                newboard.updateScore(tempms);
                return true;
            }

        }
    }
        
    //*Checkmate = true;
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

move ChessBoard::bestMove(board newboard,bool newturn, int depth,bool* Checkmate) {
    std::vector<move> Movesthisturn = getLegalMoves(newboard, newturn);
    int itr = 0;
    if (depth == 0) {
        move m (-1,-1,-1,-1);
        while (itr<Movesthisturn.size())
        {
            if (playMoveAI(Movesthisturn[itr], newboard , newturn, Movesthisturn,Checkmate)) {
                m = Movesthisturn[itr];
                break;
            }
            itr++;
        }
        return m;
    }

    move BestMove;
    int oldScore = newturn == 1 ? (INT_MIN) : (INT_MAX);


    for (int i = 0; i < Movesthisturn.size(); ++i)
    {
        if (playMoveAI(Movesthisturn[i], newboard, newturn, Movesthisturn, Checkmate)) {
            board recursionBoard = createnewboard(Movesthisturn[i], newboard);
            bool* checkmate = new bool(false);
            move bestOpponentMove = bestMove(recursionBoard, !newturn, depth - 1,checkmate);
            board bestOpponentBoard = createnewboard(bestOpponentMove, recursionBoard);
            int newScore = bestOpponentBoard.score;
            if (newturn == 1 && (newScore > oldScore) && newScore < 50) {
                BestMove = Movesthisturn[i];
                oldScore = newScore;
            }
            if (newturn == 0 && (oldScore > newScore) && oldScore > -50) {
                BestMove = Movesthisturn[i];
                oldScore = newScore;
            }
            delete checkmate;
        }
        else {
            Movesthisturn.erase(Movesthisturn.begin() + i);
            i--;
        }
    }
    if (Movesthisturn.size() == 0) {
        *Checkmate = true;
    }
    return BestMove;
}

bool ChessBoard::nextTurn()
{
    turn = !turn;
    return turn;
}
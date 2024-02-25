#include <vector>
#include "chessBoard.h"

move::move(int oldX, int oldY, int newX, int newY)
{
    oX = oldX;
    oY = oldY;
    X = newX;
    Y = newY;
}

void ChessBoard::wPawn(std::vector<move>& moves, int x, int y, board newboard)
{
    if (newboard.arr[x][y] == 0)
    {
        if (y > 0)
        {
            if (newboard.arr[x][y - 1] == -1)
            {
                moves.push_back(move(x, y, x, y - 1));
                if (newboard.arr[x][y - 2] == -1 && y == 6)
                {
                    moves.push_back(move(x, y, x, y - 2));
                }
            }
            if (x > 0)
            {
                if (newboard.arr[x - 1][y - 1] >= 6)
                {
                    moves.push_back(move(x, y, x - 1, y - 1));
                }
            }
            if (x < 7)
            {
                if (newboard.arr[x + 1][y - 1] >= 6)
                {
                    moves.push_back(move(x, y, x + 1, y - 1));
                }
            }
        }
    }
}

void ChessBoard::bPawn(std::vector<move>& moves, int x, int y, board newboard)
{
    if (newboard.arr[x][y] == 6)
    {
        if (y < 7)
        {
            if (newboard.arr[x][y + 1] == -1)
            {
                moves.push_back(move(x, y, x, y + 1));
                if (newboard.arr[x][y + 2] == -1 && y == 1)
                {
                    moves.push_back(move(x, y, x, y + 2));
                }
            }
            if (x > 0)
            {
                if (newboard.arr[x - 1][y + 1] < 6 && newboard.arr[x - 1][y + 1] != -1)
                {
                    moves.push_back(move(x, y, x - 1, y + 1));
                }
            }
            if (x < 7)
            {
                if (newboard.arr[x + 1][y + 1] < 6 && newboard.arr[x + 1][y + 1] != -1)
                {
                    moves.push_back(move(x, y, x + 1, y + 1));
                }
            }
        }
    }
}
void ChessBoard::King(std::vector<move>& moves, int x, int y, board newboard)
{
    if (newboard.arr[x][y] == 4 || newboard.arr[x][y] == 10)
    {
        bool pThreshold = newboard.arr[x][y] < 6;
        if (x > 0)
        {
            if ((pThreshold && (newboard.arr[x - 1][y] > 5 || newboard.arr[x - 1][y] == -1)) || (!pThreshold && (newboard.arr[x - 1][y] < 6 || newboard.arr[x - 1][y] == -1)))
            {
                moves.push_back(move(x, y, x - 1, y));
            }
        }
        if (x > 0 && y > 0)
        {
            if ((pThreshold && (newboard.arr[x - 1][y - 1] > 5 || newboard.arr[x - 1][y - 1] == -1)) || (!pThreshold && (newboard.arr[x - 1][y - 1] < 6 || newboard.arr[x - 1][y - 1] == -1)))
            {
                moves.push_back(move(x, y, x - 1, y - 1));
            }
        }
        if (x > 0 && y < 7)
        {
            if ((pThreshold && (newboard.arr[x - 1][y + 1] > 5 || newboard.arr[x - 1][y + 1] == -1)) || (!pThreshold && (newboard.arr[x - 1][y + 1] < 6 || newboard.arr[x - 1][y + 1] == -1)))
            {
                moves.push_back(move(x, y, x - 1, y + 1));
            }
        }
        if (y > 0)
        {
            if ((pThreshold && (newboard.arr[x][y - 1] > 5 || newboard.arr[x][y - 1] == -1)) || (!pThreshold && (newboard.arr[x][y - 1] < 6 || newboard.arr[x][y - 1] == -1)))
            {
                moves.push_back(move(x, y, x, y - 1));
            }
        }
        if (y < 7)
        {
            if ((pThreshold && (newboard.arr[x][y + 1] > 5 || newboard.arr[x][y + 1] == -1)) || (!pThreshold && (newboard.arr[x][y + 1] < 6 || newboard.arr[x][y + 1] == -1)))
            {
                moves.push_back(move(x, y, x, y + 1));
            }
        }
        if (x < 7)
        {

            if ((pThreshold && (newboard.arr[x + 1][y] > 5 || newboard.arr[x + 1][y] == -1)) || (!pThreshold && (newboard.arr[x + 1][y] < 6 || newboard.arr[x + 1][y] == -1)))
            {
                moves.push_back(move(x, y, x + 1, y));
            }
        }
        if (x < 7 && y < 7)
        {

            if ((pThreshold && (newboard.arr[x + 1][y + 1] > 5 || newboard.arr[x + 1][y + 1] == -1)) || (!pThreshold && (newboard.arr[x + 1][y + 1] < 6 || newboard.arr[x + 1][y + 1] == -1)))
            {
                moves.push_back(move(x, y, x + 1, y + 1));
            }
        }
        if (x < 7 && y > 0)
        {

            if ((pThreshold && (newboard.arr[x + 1][y - 1] > 5 || newboard.arr[x + 1][y - 1] == -1)) || (!pThreshold && (newboard.arr[x + 1][y - 1] < 6 || newboard.arr[x + 1][y - 1] == -1)))
            {
                moves.push_back(move(x, y, x + 1, y - 1));
            }
        }
        //if(canwKingKcastle || canwKingQcastle)
    }
}

void ChessBoard::Knight(std::vector<move>& moves, int x, int y, board newboard)
{
    if (newboard.arr[x][y] == 2 || newboard.arr[x][y] == 8)
    {
        bool pThreshold = newboard.arr[x][y] < 6;
        if (x > 0 && y < 6)
        {
            if ((pThreshold && (newboard.arr[x - 1][y + 2] > 5 || newboard.arr[x - 1][y + 2] == -1)) || (!pThreshold && (newboard.arr[x - 1][y + 2] < 6 || newboard.arr[x - 1][y + 2] == -1)))
            {
                moves.push_back(move(x, y, x - 1, y + 2));
            }
        }
        if (x > 0 && y > 1)
        {
            if ((pThreshold && (newboard.arr[x - 1][y - 2] > 5 || newboard.arr[x - 1][y - 2] == -1)) || (!pThreshold && (newboard.arr[x - 1][y - 2] < 6 || newboard.arr[x - 1][y - 2] == -1)))
            {
                moves.push_back(move(x, y, x - 1, y - 2));
            }
        }
        if (x > 1 && y < 7)
        {
            if ((pThreshold && (newboard.arr[x - 2][y + 1] > 5 || newboard.arr[x - 2][y + 1] == -1)) || (!pThreshold && (newboard.arr[x - 2][y + 1] < 6 || newboard.arr[x - 2][y + 1] == -1)))
            {
                moves.push_back(move(x, y, x - 2, y + 1));
            }
        }
        if (y > 0 && x > 1)
        {
            if ((pThreshold && (newboard.arr[x - 2][y - 1] > 5 || newboard.arr[x - 2][y - 1] == -1)) || (!pThreshold && (newboard.arr[x - 2][y - 1] < 6 || newboard.arr[x - 2][y - 1] == -1)))
            {
                moves.push_back(move(x, y, x - 2, y - 1));
            }
        }
        if (y < 6 && x < 7)
        {
            if ((pThreshold && (newboard.arr[x + 1][y + 2] > 5 || newboard.arr[x + 1][y + 2] == -1)) || (!pThreshold && (newboard.arr[x + 1][y + 2] < 6 || newboard.arr[x + 1][y + 2] == -1)))
            {
                moves.push_back(move(x, y, x + 1, y + 2));
            }
        }
        if (x < 7 && y > 1)
        {

            if ((pThreshold && (newboard.arr[x + 1][y - 2] > 5 || newboard.arr[x + 1][y - 2] == -1)) || (!pThreshold && (newboard.arr[x + 1][y - 2] < 6 || newboard.arr[x + 1][y - 2] == -1)))
            {
                moves.push_back(move(x, y, x + 1, y - 2));
            }
        }
        if (x < 6 && y < 7)
        {

            if ((pThreshold && (newboard.arr[x + 2][y + 1] > 5 || newboard.arr[x + 2][y + 1] == -1)) || (!pThreshold && (newboard.arr[x + 2][y + 1] < 6 || newboard.arr[x + 2][y + 1] == -1)))
            {
                moves.push_back(move(x, y, x + 2, y + 1));
            }
        }
        if (x < 6 && y > 0)
        {

            if ((pThreshold && (newboard.arr[x + 2][y - 1] > 5 || newboard.arr[x + 2][y - 1] == -1)) || (!pThreshold && (newboard.arr[x + 2][y - 1] < 6 || newboard.arr[x + 2][y - 1] == -1)))
            {
                moves.push_back(move(x, y, x + 2, y - 1));
            }
        }
    }
}

void ChessBoard::Rook(std::vector<move>& moves, int x, int y, board newboard)
{
    /*if (newboard.arr[x][y] == 1 || newboard.arr[x][y] == 7 || newboard.arr[x][y] == 5 || newboard.arr[x][y] == 11)
    {*/
        bool pThreshold = newboard.arr[x][y] < 6;
        int offX = 0;
        int offY = 0;
        bool stop = false;
        while (!stop)
        {
            ++offX;
            if (x + offX > 7 || x + offX < 0 || y + offY > 7 || y + offY < 0)
            {
                stop = true;
            }
            else
            {
                if (newboard.arr[x + offX][y + offY] == -1)
                {
                    moves.push_back(move(x, y, x + offX, y + offY));
                }
                else if ((pThreshold && newboard.arr[x + offX][y + offY] > 5) || (!pThreshold && newboard.arr[x + offX][y + offY] < 6))
                {
                    moves.push_back(move(x, y, x + offX, y + offY));
                    stop = true;
                }
                else
                {
                    stop = true;
                }
            }
        }
        offX = 0;
        offY = 0;
        stop = false;
        while (!stop)
        {
            --offX;
            if (x + offX > 7 || x + offX < 0 || y + offY > 7 || y + offY < 0)
            {
                stop = true;
            }
            else
            {
                if (newboard.arr[x + offX][y + offY] == -1)
                {
                    moves.push_back(move(x, y, x + offX, y + offY));
                }
                else if ((pThreshold && newboard.arr[x + offX][y + offY] > 5) || (!pThreshold && newboard.arr[x + offX][y + offY] < 6))
                {
                    moves.push_back(move(x, y, x + offX, y + offY));
                    stop = true;
                }
                else
                {
                    stop = true;
                }
            }
        }
        offX = 0;
        offY = 0;
        stop = false;
        while (!stop)
        {
            ++offY;
            if (x + offX > 7 || x + offX < 0 || y + offY > 7 || y + offY < 0)
            {
                stop = true;
            }
            else
            {
                if (newboard.arr[x + offX][y + offY] == -1)
                {
                    moves.push_back(move(x, y, x + offX, y + offY));
                }
                else if ((pThreshold && newboard.arr[x + offX][y + offY] > 5) || (!pThreshold && newboard.arr[x + offX][y + offY] < 6))
                {
                    moves.push_back(move(x, y, x + offX, y + offY));
                    stop = true;
                }
                else
                {
                    stop = true;
                }
            }
        }
        offX = 0;
        offY = 0;
        stop = false;
        while (!stop)
        {
            --offY;
            if (x + offX > 7 || x + offX < 0 || y + offY > 7 || y + offY < 0)
            {
                stop = true;
            }
            else
            {
                if (newboard.arr[x + offX][y + offY] == -1)
                {
                    moves.push_back(move(x, y, x + offX, y + offY));
                }
                else if ((pThreshold && newboard.arr[x + offX][y + offY] > 5) || (!pThreshold && newboard.arr[x + offX][y + offY] < 6))
                {
                    moves.push_back(move(x, y, x + offX, y + offY));
                    stop = true;
                }
                else
                {
                    stop = true;
                }
            }
        }
    //}
}

void ChessBoard::Bishop(std::vector<move>& moves, int x, int y, board newboard)
{
    /*if (newboard.arr[x][y] == 3 || newboard.arr[x][y] == 9 || newboard.arr[x][y] == 5 || newboard.arr[x][y] == 11)
    {*/
        bool pThreshold = newboard.arr[x][y] < 6;
        int offX = 0;
        int offY = 0;
        bool stop = false;
        while (!stop)
        {
            ++offX;
            ++offY;
            if (x + offX > 7 || x + offX < 0 || y + offY > 7 || y + offY < 0)
            {
                stop = true;
            }
            else
            {
                if (newboard.arr[x + offX][y + offY] == -1)
                {
                    moves.push_back(move(x, y, x + offX, y + offY));
                }
                else if ((pThreshold && newboard.arr[x + offX][y + offY] > 5) || (!pThreshold && newboard.arr[x + offX][y + offY] < 6))
                {
                    moves.push_back(move(x, y, x + offX, y + offY));
                    stop = true;
                }
                else
                {
                    stop = true;
                }
            }
        }
        offX = 0;
        offY = 0;
        stop = false;
        while (!stop)
        {
            --offX;
            --offY;
            if (x + offX > 7 || x + offX < 0 || y + offY > 7 || y + offY < 0)
            {
                stop = true;
            }
            else
            {
                if (newboard.arr[x + offX][y + offY] == -1)
                {
                    moves.push_back(move(x, y, x + offX, y + offY));
                }
                else if ((pThreshold && newboard.arr[x + offX][y + offY] > 5) || (!pThreshold && newboard.arr[x + offX][y + offY] < 6))
                {
                    moves.push_back(move(x, y, x + offX, y + offY));
                    stop = true;
                }
                else
                {
                    stop = true;
                }
            }
        }
        offX = 0;
        offY = 0;
        stop = false;
        while (!stop)
        {
            --offX;
            ++offY;
            if (x + offX > 7 || x + offX < 0 || y + offY > 7 || y + offY < 0)
            {
                stop = true;
            }
            else
            {
                if (newboard.arr[x + offX][y + offY] == -1)
                {
                    moves.push_back(move(x, y, x + offX, y + offY));
                }
                else if ((pThreshold && newboard.arr[x + offX][y + offY] > 5) || (!pThreshold && newboard.arr[x + offX][y + offY] < 6))
                {
                    moves.push_back(move(x, y, x + offX, y + offY));
                    stop = true;
                }
                else
                {
                    stop = true;
                }
            }
        }
        offX = 0;
        offY = 0;
        stop = false;
        while (!stop)
        {
            ++offX;
            --offY;
            if (x + offX > 7 || x + offX < 0 || y + offY > 7 || y + offY < 0)
            {
                stop = true;
            }
            else
            {
                if (newboard.arr[x + offX][y + offY] == -1)
                {
                    moves.push_back(move(x, y, x + offX, y + offY));
                }
                else if ((pThreshold && newboard.arr[x + offX][y + offY] > 5) || (!pThreshold && newboard.arr[x + offX][y + offY] < 6))
                {
                    moves.push_back(move(x, y, x + offX, y + offY));
                    stop = true;
                }
                else
                {
                    stop = true;
                }
            }
        }
    //}
}

void ChessBoard::Queen(std::vector<move>& moves, int x, int y, board newboard)
{
    if (newboard.arr[x][y] == 5 || newboard.arr[x][y] == 11)
    {
        Rook(moves, x, y, newboard);
        Bishop(moves, x, y, newboard);
    }
}

std::vector<move> ChessBoard::getLegalMoves(board b, bool color)
{
    std::vector<move> moves;

    for (int i = 0; i < 8; ++i)
    {
        for (int j = 0; j < 8; ++j)
        {
            if (color == 1)
            {
                if (b.arr[i][j] == 0)
                {
                    wPawn(moves, i, j,b);
                }
                else if (b.arr[i][j] == 4)
                {
                    King(moves, i, j, b);
                }
                else if (b.arr[i][j] == 2)
                {
                    Knight(moves, i, j, b);
                }
                else if (b.arr[i][j] == 1)
                {
                    Rook(moves, i, j, b);
                }
                else if (b.arr[i][j] == 3)
                {
                    Bishop(moves, i, j, b);
                }
                else if (b.arr[i][j] == 5)
                {
                    Queen(moves, i, j, b);
                }
            }
            else
            {
                if (b.arr[i][j] == 6)
                {
                    bPawn(moves, i, j, b);
                }
                else if (b.arr[i][j] == 10)
                {
                    King(moves, i, j, b);
                }
                else if (b.arr[i][j] == 8)
                {
                    Knight(moves, i, j, b);
                }
                else if (b.arr[i][j] == 7)
                {
                    Rook(moves, i, j, b);
                }
                else if (b.arr[i][j] == 9)
                {
                    Bishop(moves, i, j, b);
                }
                else if (b.arr[i][j] == 11)
                {
                    Queen(moves, i, j, b);
                }
            }
        }
    }
    // for (int i = 0; i < moves.size(); ++i)
    // {
    //     std::cout << moves[i].oX << " " << moves[i].oY << " " << moves[i].X << " " << moves[i].Y << "\n";
    // }
    return moves;
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
                if (currBoard.arr[req.X][req.Y] == 4) {
                    canwKingKcastle = false;
                    canwKingQcastle = false;
                }if (currBoard.arr[req.X][req.Y] == 10) {
                    canwKingKcastle = false;
                    canwKingQcastle = false;
                }
                history.push_back(currBoard);
                return true;
            }
        }
    }
    return false;
}

bool ChessBoard::playMove(move req , board newboard , bool newturn , std::vector<move> movesthisTurn)
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



int ChessBoard::score() {
    int score = 0;
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            if (currBoard.arr[i][j] == 0) score += 1;
            if (currBoard.arr[i][j] == 1) score += 5;
            if (currBoard.arr[i][j] == 2) score += 3;
            if (currBoard.arr[i][j] == 3) score += 3;
            if (currBoard.arr[i][j] == 4) score += INT_MAX;
            if (currBoard.arr[i][j] == 5) score += 9;
            if (currBoard.arr[i][j] == 6) score -= 1;
            if (currBoard.arr[i][j] == 7) score -= 5;
            if (currBoard.arr[i][j] == 8) score -= 3;
            if (currBoard.arr[i][j] == 9) score -= 3;
            if (currBoard.arr[i][j] == 10) score -= INT_MAX;
            if (currBoard.arr[i][j] == 11) score -= 9;
        }
    }
    return score;
}

int ChessBoard::score(board board) {
    int score = 0;
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            if (board.arr[i][j] == 0) score += 1;
            if (board.arr[i][j] == 1) score += 5;
            if (board.arr[i][j] == 2) score += 3;
            if (board.arr[i][j] == 3) score += 3;
            if (board.arr[i][j] == 4) score += INT_MAX;
            if (board.arr[i][j] == 5) score += 9;
            if (board.arr[i][j] == 6) score -= 1;
            if (board.arr[i][j] == 7) score -= 5;
            if (board.arr[i][j] == 8) score -= 3;
            if (board.arr[i][j] == 9) score -= 3;
            if (board.arr[i][j] == 10) score -= INT_MAX;
            if (board.arr[i][j] == 11) score -= 9;
        }
    }
    return score;
}

board createnewboard(move m , board& currgoingboard) {
    board ans = currgoingboard;
    ans.arr[m.X%8][m.Y%8] = ans.arr[m.oX%8][m.oY%8];
    ans.arr[m.oX%8][m.oY%8] = -1;
    return ans;
}

move ChessBoard::bestMove(board newboard,bool newturn, int depth) {
    std::vector<move> Movesthisturn = getLegalMoves(newboard, newturn);
    int itr = 0;
    if (depth == 0) {
        move m (-1,-1,-1,-1);
        while (itr<Movesthisturn.size())
        {
            if (playMove(Movesthisturn[itr], newboard , newturn, Movesthisturn)) {
                m = Movesthisturn[itr];
                break;
            }
            itr++;
        }
        return m;
    }

    move BestMove/* = Movesthisturn[itr]*/;
    int oldScore = newturn == 1 ? (INT_MIN) : (INT_MAX);


    for (int i = 0; i < Movesthisturn.size(); ++i)
    {
        if (playMove(Movesthisturn[i], newboard , newturn, Movesthisturn)) {
            board recursionBoard = createnewboard(Movesthisturn[i], newboard);
            move bestOpponentMove = bestMove(recursionBoard, !newturn, depth - 1);
            if (bestOpponentMove.X == -1) {
                return move(-1, -1, -1, -1);
            }
            board bestOpponentBoard = createnewboard(bestOpponentMove, recursionBoard);
            int newScore = score(bestOpponentBoard);
            if (newturn == 1 && (newScore >= oldScore) && newScore<50) {
                BestMove = Movesthisturn[i];
                oldScore = newScore;
            }
            if (newturn == 0 && oldScore >= newScore && oldScore>-50) {
                BestMove = Movesthisturn[i];
                oldScore = newScore;
            }
        }
    }
    return BestMove;
}


bool ChessBoard::nextTurn()
{
    turn = !turn;
    return turn;
}
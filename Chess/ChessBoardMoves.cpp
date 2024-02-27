#include <vector>
#include "chessBoard.h"

//pawn,king,knight are jumping pieces that can jump to their desired location
//rook,bishop,Queen are sliding pieces that can slide to their desired location so can be stopped

void ChessBoard::wPawn(std::vector<move>& moves, int x, int y, board newboard)
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

void ChessBoard::bPawn(std::vector<move>& moves, int x, int y, board newboard)
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

void ChessBoard::King(std::vector<move>& moves, int x, int y, board newboard)//refine this code
{
    bool pThreshold = newboard.arr[x][y] < 6;
    if (x > 0)
    {
        if (newboard.arr[x - 1][y] == -1 || (pThreshold && newboard.arr[x - 1][y] > 5 ) || (!pThreshold && newboard.arr[x - 1][y] < 6 ))
        {
            moves.push_back(move(x, y, x - 1, y));
        }
    }
    if (x > 0 && y > 0)
    {
        if (newboard.arr[x - 1][y - 1] == -1 || (pThreshold && newboard.arr[x - 1][y - 1] > 5 ) || (!pThreshold && newboard.arr[x - 1][y - 1] < 6 ))
        {
            moves.push_back(move(x, y, x - 1, y - 1));
        }
    }
    if (x > 0 && y < 7)
    {
        if (newboard.arr[x - 1][y + 1] == -1 || (pThreshold && newboard.arr[x - 1][y + 1] > 5 ) || (!pThreshold && newboard.arr[x - 1][y + 1] < 6 ))
        {
            moves.push_back(move(x, y, x - 1, y + 1));
        }
    }
    if (y > 0)
    {
        if (newboard.arr[x][y - 1] == -1 || (pThreshold && newboard.arr[x][y - 1] > 5 ) || (!pThreshold &&  newboard.arr[x][y - 1] < 6 ))
        {
            moves.push_back(move(x, y, x, y - 1));
        }
    }
    if (y < 7)
    {
        if (newboard.arr[x][y + 1] == -1 || (pThreshold && newboard.arr[x][y + 1] > 5 ) || (!pThreshold && newboard.arr[x][y + 1] < 6))
        {
            moves.push_back(move(x, y, x, y + 1));
        }
    }
    if (x < 7)
    {

        if (newboard.arr[x + 1][y] == -1 || (pThreshold && newboard.arr[x + 1][y] > 5 ) || !pThreshold && (newboard.arr[x + 1][y] < 6 ))
        {
            moves.push_back(move(x, y, x + 1, y));
        }
    }
    if (x < 7 && y < 7)
    {

        if (newboard.arr[x + 1][y + 1] == -1 || (pThreshold && newboard.arr[x + 1][y + 1] > 5) || (!pThreshold && newboard.arr[x + 1][y + 1] < 6 ))
        {
            moves.push_back(move(x, y, x + 1, y + 1));
        }
    }
    if (x < 7 && y > 0)
    {

        if (newboard.arr[x + 1][y - 1] == -1 || (pThreshold && newboard.arr[x + 1][y - 1] > 5 ) || (!pThreshold && newboard.arr[x + 1][y - 1] < 6 ))
        {
            moves.push_back(move(x, y, x + 1, y - 1));
        }
    }
}

void ChessBoard::Knight(std::vector<move>& moves, int x, int y, board newboard)
{
    bool pThreshold = newboard.arr[x][y] < 6;
    if (x > 0)
    {
        if (y < 6) {
            if (newboard.arr[x - 1][y + 2] == -1 || (pThreshold && newboard.arr[x - 1][y + 2] > 5) || (!pThreshold && newboard.arr[x - 1][y + 2] < 6))
            {
                moves.push_back(move(x, y, x - 1, y + 2));
            }
        }
        if (y > 1) {
            if (newboard.arr[x - 1][y - 2] == -1 || (pThreshold && newboard.arr[x - 1][y - 2] > 5) || (!pThreshold && newboard.arr[x - 1][y - 2] < 6))
            {
                moves.push_back(move(x, y, x - 1, y - 2));
            }
        }
    }
    if (x > 1)
    {
        if (y < 7) {
            if (newboard.arr[x - 2][y + 1] == -1 || (pThreshold && newboard.arr[x - 2][y + 1] > 5) || (!pThreshold && newboard.arr[x - 2][y + 1] < 6))
            {
                moves.push_back(move(x, y, x - 2, y + 1));
            }
        }
        if (y > 0) {
            if (newboard.arr[x - 2][y - 1] == -1 || (pThreshold && newboard.arr[x - 2][y - 1] > 5) || (!pThreshold && newboard.arr[x - 2][y - 1] < 6))
            {
                moves.push_back(move(x, y, x - 2, y - 1));
            }
        }
    }
    if (x < 7)
    {
        if (y < 6) {
            if (newboard.arr[x + 1][y + 2] == -1 || (pThreshold && newboard.arr[x + 1][y + 2] > 5) || (!pThreshold && newboard.arr[x + 1][y + 2] < 6))
            {
                moves.push_back(move(x, y, x + 1, y + 2));
            }
        }
        if (y > 1) {
            if (newboard.arr[x + 1][y - 2] == -1 || (pThreshold && newboard.arr[x + 1][y - 2] > 5) || (!pThreshold && newboard.arr[x + 1][y - 2] < 6))
            {
                moves.push_back(move(x, y, x + 1, y - 2));
            }
        }
    }
    if (x < 6)
    {
        if (y < 7) {
            if (newboard.arr[x + 2][y + 1] == -1 || (pThreshold && newboard.arr[x + 2][y + 1] > 5) || (!pThreshold && newboard.arr[x + 2][y + 1] < 6))
            {
                moves.push_back(move(x, y, x + 2, y + 1));
            }
        }
        if (y > 0) {
            if (newboard.arr[x + 2][y - 1] == -1 || (pThreshold && newboard.arr[x + 2][y - 1] > 5) || (!pThreshold && newboard.arr[x + 2][y - 1] < 6))
            {
                moves.push_back(move(x, y, x + 2, y - 1));
            }
        }
    }
}

void SlideHelper(std::vector<move>& moves, bool pThreshold, int x, int y, int offX, int offY, board newboard, bool* stop) {
    if (x + offX > 7 || x + offX < 0 || y + offY > 7 || y + offY < 0)
    {
        *stop = true;
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
            *stop = true;
        }
        else
        {
            *stop = true;
        }
    }
}

void ChessBoard::Rook(std::vector<move>& moves, int x, int y, board newboard)
{
    bool pThreshold = newboard.arr[x][y] < 6;
    int offX = 0;
    int offY = 0;
    bool stop = false;
    while (!stop)
    {
        ++offX;
        SlideHelper(moves, pThreshold, x, y, offX, offY, newboard, &stop);
    }
    offX = 0;
    offY = 0;
    stop = false;
    while (!stop)
    {
        --offX;
        SlideHelper(moves, pThreshold, x, y, offX, offY, newboard, &stop);
    }
    offX = 0;
    offY = 0;
    stop = false;
    while (!stop)
    {
        ++offY;
        SlideHelper(moves, pThreshold, x, y, offX, offY, newboard, &stop);
    }
    offX = 0;
    offY = 0;
    stop = false;
    while (!stop)
    {
        --offY;
        SlideHelper(moves, pThreshold, x, y, offX, offY, newboard, &stop);
    }
}

void ChessBoard::Bishop(std::vector<move>& moves, int x, int y, board newboard)
{
    bool pThreshold = newboard.arr[x][y] < 6;
    int offX = 0;
    int offY = 0;
    bool stop = false;
    while (!stop)
    {
        ++offX;
        ++offY;
        SlideHelper(moves, pThreshold, x, y, offX, offY, newboard, &stop);
    }
    offX = 0;
    offY = 0;
    stop = false;
    while (!stop)
    {
        --offX;
        --offY;
        SlideHelper(moves, pThreshold, x, y, offX, offY, newboard, &stop);
    }
    offX = 0;
    offY = 0;
    stop = false;
    while (!stop)
    {
        --offX;
        ++offY;
        SlideHelper(moves, pThreshold, x, y, offX, offY, newboard, &stop);
    }
    offX = 0;
    offY = 0;
    stop = false;
    while (!stop)
    {
        ++offX;
        --offY;
        SlideHelper(moves, pThreshold, x, y, offX, offY, newboard, &stop);
    }
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
                    wPawn(moves, i, j, b);
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
    return moves;
}

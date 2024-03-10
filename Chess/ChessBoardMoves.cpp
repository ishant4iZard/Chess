#include <vector>
#include "chessBoard.h"

//pawn,king,knight are jumping pieces that can jump to their desired location
//rook,bishop,Queen are sliding pieces that can slide to their desired location so can be stopped

struct offset {
    int x, y;
};

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

    offset Off[8] = { {1, 1}, {1, -1}, {-1, 1}, {-1, -1}, {1, 0}, {-1, 0}, {0, 1}, {0, -1} };

    for (int i = 0; i < 8; i++) {
        int newx = x + Off[i].x;
        int newy = y + Off[i].y;
        if (newx >= 0 && newx < 8 && newy >= 0 && newy < 8) {
            if (newboard.arr[newx][newy] == -1 || (pThreshold && newboard.arr[newx][newy] > 5) || (!pThreshold && newboard.arr[newx][newy] < 6))
            {
                moves.push_back(move(x, y, newx, newy));
            }
        }
    }
    if (pThreshold && x == 4 && y == 7 && newboard.arr[x + 3][y] == 1 && newboard.arr[x + 1][y] == -1 && newboard.arr[x + 2][y] == -1&&canwKingKcastle) {
        moves.push_back(move(x, y, x + 2, y));
    }
    if (pThreshold && x == 4 && y == 7 && newboard.arr[x -4][y] == 1 && newboard.arr[x - 1][y] == -1 && newboard.arr[x - 2][y] == -1 && newboard.arr[x - 3][y] == -1 && canwKingQcastle) {
        moves.push_back(move(x, y, x - 2, y));
    }
    if (!pThreshold && x == 4 && y == 0 && newboard.arr[x + 3][y] == 7 && newboard.arr[x + 1][y] == -1 && newboard.arr[x + 2][y] == -1 && canbKingKcastle) {
        moves.push_back(move(x, y, x + 2, y));
    }
    if (!pThreshold && x == 4 && y == 0 && newboard.arr[x - 4][y] == 7 && newboard.arr[x - 1][y] == -1 && newboard.arr[x - 2][y] == -1 && newboard.arr[x - 3][y] == -1 && canbKingQcastle) {
        moves.push_back(move(x, y, x - 2, y));
    }
}

void ChessBoard::Knight(std::vector<move>& moves, int x, int y, board newboard)
{
    bool pThreshold = newboard.arr[x][y] < 6;

    offset Off[8] = {{2, 1}, {2, -1}, {-2, 1}, {-2, -1}, {1, 2}, {1, -2}, {-1, 2}, {-1, -2}};

    for (int i = 0; i < 8; i++) {
        int newx = x + Off[i].x;
        int newy = y + Off[i].y;
        if (newx >= 0 && newx < 8 && newy >= 0 && newy < 8) {
            if (newboard.arr[newx][newy] == -1 || (pThreshold && newboard.arr[newx][newy] > 5) || (!pThreshold && newboard.arr[newx][newy] < 6))
            {
                moves.push_back(move(x, y, newx, newy));
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

    offset Off[4] = { { 1,0 }, {-1, 0},{0,1},{0,-1} };

    for (int i = 0; i < 4; i++) {
        bool stop = false;
        int multiplier = 1;
        while (!stop)
        {
            SlideHelper(moves, pThreshold, x, y, Off[i].x * multiplier, Off[i].y * multiplier, newboard, &stop);
            multiplier++;
        }
    }
}

void ChessBoard::Bishop(std::vector<move>& moves, int x, int y, board newboard)
{
    bool pThreshold = newboard.arr[x][y] < 6;

    offset Off[4] = { { 1,1 }, {-1, 1},{1,-1},{-1,-1} };

    for (int i = 0; i < 4; i++) {
        bool stop = false;
        int multiplier = 1;
        while (!stop)
        {
            SlideHelper(moves, pThreshold, x, y, Off[i].x * multiplier, Off[i].y * multiplier, newboard, &stop);
            multiplier++;
        }
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
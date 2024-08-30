#include <vector>
#include "chessBoard.h"

enum PieceType {
    EMPTY = -1,
    WHITE_PAWN = 0,
    WHITE_KNIGHT = 2,
    WHITE_ROOK = 1,
    WHITE_BISHOP = 3,
    WHITE_QUEEN = 5,
    WHITE_KING = 4,
    BLACK_PAWN = 6,
    BLACK_KNIGHT = 8,
    BLACK_ROOK = 7,
    BLACK_BISHOP = 9,
    BLACK_QUEEN = 11,
    BLACK_KING = 10
};

struct Offset {
    int x, y;
};

inline bool isInBounds(int x, int y) {
    return x >= 0 && x < 8 && y >= 0 && y < 8;
}

void ChessBoard::wPawn(std::vector<move>& moves, int x, int y, board newboard) {
    if (y > 0) {
        if (newboard.arr[x][y - 1] == EMPTY) {
            moves.push_back(move(x, y, x, y - 1));
            if (y == 6 && newboard.arr[x][y - 2] == EMPTY) {
                moves.push_back(move(x, y, x, y - 2));
            }
        }
        if (x > 0 && newboard.arr[x - 1][y - 1] >= BLACK_PAWN) {
            moves.push_back(move(x, y, x - 1, y - 1));
        }
        if (x < 7 && newboard.arr[x + 1][y - 1] >= BLACK_PAWN) {
            moves.push_back(move(x, y, x + 1, y - 1));
        }
    }
}

void ChessBoard::bPawn(std::vector<move>& moves, int x, int y, board newboard) {
    if (y < 7) {
        if (newboard.arr[x][y + 1] == EMPTY) {
            moves.push_back(move(x, y, x, y + 1));
            if (y == 1 && newboard.arr[x][y + 2] == EMPTY) {
                moves.push_back(move(x, y, x, y + 2));
            }
        }
        if (x > 0 && newboard.arr[x - 1][y + 1] < BLACK_PAWN && newboard.arr[x - 1][y + 1] != EMPTY) {
            moves.push_back(move(x, y, x - 1, y + 1));
        }
        if (x < 7 && newboard.arr[x + 1][y + 1] < BLACK_PAWN && newboard.arr[x + 1][y + 1] != EMPTY) {
            moves.push_back(move(x, y, x + 1, y + 1));
        }
    }
}

void ChessBoard::King(std::vector<move>& moves, int x, int y, board newboard) {
    bool isWhite = newboard.arr[x][y] < BLACK_PAWN;

    Offset offsets[8] = { {1, 1}, {1, -1}, {-1, 1}, {-1, -1}, {1, 0}, {-1, 0}, {0, 1}, {0, -1} };

    for (const auto& offset : offsets) {
        int newx = x + offset.x;
        int newy = y + offset.y;
        if (isInBounds(newx, newy)) {
            if (newboard.arr[newx][newy] == EMPTY || (isWhite && newboard.arr[newx][newy] >= BLACK_PAWN) || (!isWhite && newboard.arr[newx][newy] < BLACK_PAWN)) {
                moves.push_back(move(x, y, newx, newy));
            }
        }
    }

    if (isWhite && x == 4 && y == 7) {
        if (newboard.arr[x + 3][y] == WHITE_ROOK && newboard.arr[x + 1][y] == EMPTY && newboard.arr[x + 2][y] == EMPTY && canwKingKcastle) {
            moves.push_back(move(x, y, x + 2, y));
        }
        if (newboard.arr[x - 4][y] == WHITE_ROOK && newboard.arr[x - 1][y] == EMPTY && newboard.arr[x - 2][y] == EMPTY && newboard.arr[x - 3][y] == EMPTY && canwKingQcastle) {
            moves.push_back(move(x, y, x - 2, y));
        }
    }

    if (!isWhite && x == 4 && y == 0) {
        if (newboard.arr[x + 3][y] == BLACK_ROOK && newboard.arr[x + 1][y] == EMPTY && newboard.arr[x + 2][y] == EMPTY && canbKingKcastle) {
            moves.push_back(move(x, y, x + 2, y));
        }
        if (newboard.arr[x - 4][y] == BLACK_ROOK && newboard.arr[x - 1][y] == EMPTY && newboard.arr[x - 2][y] == EMPTY && newboard.arr[x - 3][y] == EMPTY && canbKingQcastle) {
            moves.push_back(move(x, y, x - 2, y));
        }
    }
}

void ChessBoard::Knight(std::vector<move>& moves, int x, int y, board newboard) {
    bool isWhite = newboard.arr[x][y] < BLACK_PAWN;

    Offset offsets[8] = { {2, 1}, {2, -1}, {-2, 1}, {-2, -1}, {1, 2}, {1, -2}, {-1, 2}, {-1, -2} };

    for (const auto& offset : offsets) {
        int newx = x + offset.x;
        int newy = y + offset.y;
        if (isInBounds(newx, newy)) {
            if (newboard.arr[newx][newy] == EMPTY || (isWhite && newboard.arr[newx][newy] >= BLACK_PAWN) || (!isWhite && newboard.arr[newx][newy] < BLACK_PAWN)) {
                moves.push_back(move(x, y, newx, newy));
            }
        }
    }
}

void SlideHelper(std::vector<move>& moves, bool isWhite, int x, int y, int offX, int offY, board newboard, bool& stop) {
    int newx = x + offX;
    int newy = y + offY;

    if (!isInBounds(newx, newy)) {
        stop = true;
        return;
    }

    if (newboard.arr[newx][newy] == EMPTY) {
        moves.push_back(move(x, y, newx, newy));
    }
    else if ((isWhite && newboard.arr[newx][newy] >= BLACK_PAWN) || (!isWhite && newboard.arr[newx][newy] < BLACK_PAWN)) {
        moves.push_back(move(x, y, newx, newy));
        stop = true;
    }
    else {
        stop = true;
    }
}

void ChessBoard::Rook(std::vector<move>& moves, int x, int y, board newboard) {
    bool isWhite = newboard.arr[x][y] < BLACK_PAWN;

    Offset offsets[4] = { {1, 0}, {-1, 0}, {0, 1}, {0, -1} };

    for (const auto& offset : offsets) {
        bool stop = false;
        int multiplier = 1;
        while (!stop) {
            SlideHelper(moves, isWhite, x, y, offset.x * multiplier, offset.y * multiplier, newboard, stop);
            multiplier++;
        }
    }
}

void ChessBoard::Bishop(std::vector<move>& moves, int x, int y, board newboard) {
    bool isWhite = newboard.arr[x][y] < BLACK_PAWN;

    Offset offsets[4] = { {1, 1}, {-1, 1}, {1, -1}, {-1, -1} };

    for (const auto& offset : offsets) {
        bool stop = false;
        int multiplier = 1;
        while (!stop) {
            SlideHelper(moves, isWhite, x, y, offset.x * multiplier, offset.y * multiplier, newboard, stop);
            multiplier++;
        }
    }
}

void ChessBoard::Queen(std::vector<move>& moves, int x, int y, board newboard) {
    if (newboard.arr[x][y] == WHITE_QUEEN || newboard.arr[x][y] == BLACK_QUEEN) {
        Rook(moves, x, y, newboard);
        Bishop(moves, x, y, newboard);
    }
}

std::vector<move> ChessBoard::getLegalMoves(board b, bool color) {
    std::vector<move> moves;

    for (int i = 0; i < 8; ++i) {
        for (int j = 0; j < 8; ++j) {
            int piece = b.arr[i][j];
            if (piece == EMPTY) continue;

            bool isWhite = color == 1;
            if (isWhite && piece < BLACK_PAWN) {
                switch (piece) {
                case WHITE_PAWN: wPawn(moves, i, j, b); break;
                case WHITE_KING: King(moves, i, j, b); break;
                case WHITE_KNIGHT: Knight(moves, i, j, b); break;
                case WHITE_ROOK: Rook(moves, i, j, b); break;
                case WHITE_BISHOP: Bishop(moves, i, j, b); break;
                case WHITE_QUEEN: Queen(moves, i, j, b); break;
                }
            }
            else if (!isWhite && piece >= BLACK_PAWN) {
                switch (piece) {
                case BLACK_PAWN: bPawn(moves, i, j, b); break;
                case BLACK_KING: King(moves, i, j, b); break;
                case BLACK_KNIGHT: Knight(moves, i, j, b); break;
                case BLACK_ROOK: Rook(moves, i, j, b); break;
                case BLACK_BISHOP: Bishop(moves, i, j, b); break;
                case BLACK_QUEEN: Queen(moves, i, j, b); break;
                }
            }
        }
    }
    return moves;
}


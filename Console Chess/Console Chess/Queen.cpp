#include <cmath>
#include "Queen.h"

Queen::Queen(bool isWhite) : Piece(isWhite) {}

bool Queen::canMove(const Position& from, const Position& to, Piece* board[8][8]) const {
    int fromRow = from.getRow();
    int fromCol = from.getColumn();
    int toRow = to.getRow();
    int toCol = to.getColumn();

    int rowDiff = toRow - fromRow;
    int colDiff = toCol - fromCol;

    if (fromRow == toRow && fromCol != toCol) {
        int step = (colDiff > 0) ? 1 : -1;
        for (int col = fromCol + step; col != toCol; col += step) {
            if (board[fromRow][col] != nullptr) {
                return false;
            }
        }
    }

    else if (fromCol == toCol && fromRow != toRow) {
        int step = (rowDiff > 0) ? 1 : -1;
        for (int row = fromRow + step; row != toRow; row += step) {
            if (board[row][fromCol] != nullptr) {
                return false;
            }
        }
    }

    else if (std::abs(rowDiff) == std::abs(colDiff) && rowDiff != 0) {
        int rowStep = (rowDiff > 0) ? 1 : -1;
        int colStep = (colDiff > 0) ? 1 : -1;

        int steps = std::abs(rowDiff) - 1;
        for (int i = 1; i <= steps; i++) {
            int checkRow = fromRow + i * rowStep;
            int checkCol = fromCol + i * colStep;
            if (board[checkRow][checkCol] != nullptr) {
                return false;
            }
        }
    }
    else {
        return false;
    }

    Piece* target = board[toRow][toCol];
    return (target == nullptr) || (target->isWhitePiece() != isWhitePiece());
}

std::wstring Queen::getSymbol() const {
    return isWhite ? L"♛" : L"♕";
}
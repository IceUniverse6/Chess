#include <cmath> 
#include "Bishop.h"

Bishop::Bishop(bool isWhite) : Piece(isWhite) {}

bool Bishop::canMove(const Position& from, const Position& to, Piece* board[8][8]) const {
    int fromRow = from.getRow();
    int fromCol = from.getColumn();
    int toRow = to.getRow();
    int toCol = to.getColumn();

    int rowDiff = toRow - fromRow;
    int colDiff = toCol - fromCol;

    if (rowDiff == 0 && colDiff == 0) {
        return false;
    }

    if (std::abs(rowDiff) != std::abs(colDiff)) {
        return false;
    }

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

    Piece* target = board[toRow][toCol];
    return (target == nullptr) || (target->isWhitePiece() != isWhitePiece());
}

std::wstring Bishop::getSymbol() const {
    return isWhite ? L"♝" : L"♗";
}
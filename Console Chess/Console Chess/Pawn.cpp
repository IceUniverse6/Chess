#include <cmath>
#include "Pawn.h"

Pawn::Pawn(bool isWhite) : Piece(isWhite) {}

bool Pawn::canMove(const Position& from, const Position& to, Piece* board[8][8]) const {
    int direction = isWhite ? -1 : 1;
    int startRow = isWhite ? 6 : 1;

    int fromRow = from.getRow();
    int fromCol = from.getColumn();
    int toRow = to.getRow();
    int toCol = to.getColumn();

    int rowDiff = toRow - fromRow;
    int colDiff = toCol - fromCol;

    if (colDiff == 0 && rowDiff == direction) {
        return board[toRow][toCol] == nullptr;
    }

    if (colDiff == 0 && rowDiff == 2 * direction && fromRow == startRow) {
        int midRow = fromRow + direction;
        return board[midRow][fromCol] == nullptr && board[toRow][toCol] == nullptr;
    }

    if (std::abs(colDiff) == 1 && rowDiff == direction) {
        Piece* target = board[toRow][toCol];
        return target != nullptr && target->isWhitePiece() != isWhitePiece();
    }

    return false;
}

std::wstring Pawn::getSymbol() const {
    return isWhite ? L"♟" : L"♙";
}

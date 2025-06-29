#include <cmath>
#include "Knight.h"

Knight::Knight(bool isWhite) : Piece(isWhite) {}

bool Knight::canMove(const Position& from, const Position& to, Piece* board[8][8]) const {
    int fromRow = from.getRow();
    int fromCol = from.getColumn();
    int toRow = to.getRow();
    int toCol = to.getColumn();

    int rowDiff = std::abs(toRow - fromRow);
    int colDiff = std::abs(toCol - fromCol);

    if ((rowDiff == 2 && colDiff == 1) || (rowDiff == 1 && colDiff == 2)) {
        Piece* target = board[toRow][toCol];
        return (target == nullptr) || (target->isWhitePiece() != isWhitePiece());
    }

    return false;
}

std::wstring Knight::getSymbol() const {
    return isWhite ? L"♞" : L"♘";
}
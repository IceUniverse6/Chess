#include <cmath> 
#include "King.h"
#include "Rook.h"

King::King(bool isWhite) : Piece(isWhite), isMoved(false) {}

bool King::canMove(const Position& from, const Position& to, Piece* board[8][8]) const {
    int fromRow = from.getRow();
    int fromCol = from.getColumn();
    int toRow = to.getRow();
    int toCol = to.getColumn();

    int rowDiff = std::abs(toRow - fromRow);
    int colDiff = std::abs(toCol - fromCol);

    if (rowDiff <= 1 && colDiff <= 1) {
        Piece* target = board[toRow][toCol];
        return (target == nullptr) || (target->isWhitePiece() != isWhitePiece());
    }

    if (!isMoved && rowDiff == 0 && colDiff == 2) {
        int rookCol = (toCol > fromCol) ? 7 : 0;
        int step = (toCol > fromCol) ? 1 : -1;

        for (int col = fromCol + step; col != toCol; col += step) {
            if (board[fromRow][col] != nullptr) {
                return false;
            }
        }

        Piece* rookPiece = board[fromRow][rookCol];
        if (rookPiece == nullptr) return false;

        Rook* rook = dynamic_cast<Rook*>(rookPiece);
        if (rook == nullptr) return false;

        return (rook->isWhitePiece() == isWhitePiece()) && !rook->hasMoved();
    }

    return false;
}

std::wstring King::getSymbol() const {
    return isWhite ? L"♚" : L"♔";
}

void King::moved() {
    isMoved = true;
}

bool King::hasMoved() const {
    return isMoved;
}
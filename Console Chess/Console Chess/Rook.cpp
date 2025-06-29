#include "Rook.h"

Rook::Rook(bool isWhite) : Piece(isWhite), isMoved(false) {}

bool Rook::canMove(const Position& from, const Position& to, Piece* board[8][8]) const {
    int fromRow = from.getRow();
    int fromCol = from.getColumn();
    int toRow = to.getRow();
    int toCol = to.getColumn();

    if (fromRow == toRow && fromCol != toCol) {
        int step = (toCol > fromCol) ? 1 : -1;
        for (int col = fromCol + step; col != toCol; col += step) {
            if (board[fromRow][col] != nullptr) {
                return false;
            }
        }
    }

    else if (fromCol == toCol && fromRow != toRow) {
        int step = (toRow > fromRow) ? 1 : -1;
        for (int row = fromRow + step; row != toRow; row += step) {
            if (board[row][fromCol] != nullptr) {
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

std::wstring Rook::getSymbol() const {
    return isWhite ? L"♜" : L"♖";
}

void Rook::moved() {
    isMoved = true;
}

bool Rook::hasMoved() const {
    return isMoved;
}
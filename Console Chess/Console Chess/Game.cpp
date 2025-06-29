#include <cmath>
#include <iostream>
#include<Windows.h>
#include "Game.h"

HANDLE color = GetStdHandle(STD_OUTPUT_HANDLE);

Game::Game() : whiteTurn(true), gameOver(false) {
    for (int r = 0; r < 8; r++) {
        for (int c = 0; c < 8; c++) {
            board[r][c] = nullptr;
        }
    }
    setupInitialBoard();
}

Game::~Game() {
    for (int r = 0; r < 8; r++) {
        for (int c = 0; c < 8; c++) {
            if (board[r][c] != nullptr) {
                delete board[r][c];
                board[r][c] = nullptr;
            }
        }
    }
}

void Game::setupInitialBoard() {
    for (int c = 0; c < 8; c++) {
        board[1][c] = new Pawn(false);
        board[6][c] = new Pawn(true);
    }

    board[0][0] = new Rook(false);
    board[0][7] = new Rook(false);
    board[7][0] = new Rook(true);
    board[7][7] = new Rook(true);

    board[0][1] = new Knight(false);
    board[0][6] = new Knight(false);
    board[7][1] = new Knight(true);
    board[7][6] = new Knight(true);

    board[0][2] = new Bishop(false);
    board[0][5] = new Bishop(false);
    board[7][2] = new Bishop(true);
    board[7][5] = new Bishop(true);

    board[0][3] = new Queen(false);
    board[7][3] = new Queen(true);

    board[0][4] = new King(false);
    board[7][4] = new King(true);

    for (int r = 2; r <= 5; r++) {
        for (int c = 0; c < 8; c++) {
            board[r][c] = nullptr;
        }
    }
}

bool Game::isCheck(bool white) {
    Position kingPos(-1, -1);

    for (int r = 0; r < 8; r++) {
        for (int c = 0; c < 8; c++) {
            Piece* piece = board[r][c];
            if (piece && dynamic_cast<King*>(piece) && piece->isWhitePiece() == white) {
                kingPos = Position(r, c);
                break;
            }
        }
    }

    if (!kingPos.isValid()) return false;

    for (int r = 0; r < 8; r++) {
        for (int c = 0; c < 8; c++) {
            Piece* piece = board[r][c];
            if (piece && piece->isWhitePiece() != white) {
                if (piece->canMove(Position(r, c), kingPos, board)) {
                    return true;
                }
            }
        }
    }
    return false;
}

bool Game::canMoveAnyPiece(bool white) {
    for (int r1 = 0; r1 < 8; r1++) {
        for (int c1 = 0; c1 < 8; c1++) {
            Piece* piece = board[r1][c1];
            if (!piece || piece->isWhitePiece() != white) continue;

            for (int r2 = 0; r2 < 8; r2++) {
                for (int c2 = 0; c2 < 8; c2++) {
                    Position from(r1, c1);
                    Position to(r2, c2);

                    if (!piece->canMove(from, to, board)) continue;

                    Piece* temp = board[r2][c2];
                    board[r2][c2] = piece;
                    board[r1][c1] = nullptr;

                    bool inCheck = isCheck(white);

                    board[r1][c1] = piece;
                    board[r2][c2] = temp;

                    if (!inCheck) return true;
                }
            }
        }
    }
    return false;
}

bool Game::isCheckmate(bool white) {
    return isCheck(white) && !canMoveAnyPiece(white);
}

bool Game::isStalemate(bool white) {
    return !isCheck(white) && !canMoveAnyPiece(white);
}

bool Game::moveWouldCauseCheck(const Position& from, const Position& to) {
    Piece* piece = board[from.getRow()][from.getColumn()];
    if (!piece) return true;

    Piece* target = board[to.getRow()][to.getColumn()];
    board[to.getRow()][to.getColumn()] = piece;
    board[from.getRow()][from.getColumn()] = nullptr;

    bool inCheck = isCheck(piece->isWhitePiece());

    board[from.getRow()][from.getColumn()] = piece;
    board[to.getRow()][to.getColumn()] = target;

    return inCheck;
}

void Game::promotePawnIfNeeded(const Position& pos) {
    int row = pos.getRow();
    int col = pos.getColumn();
    Piece* piece = board[row][col];

    if (Pawn* pawn = dynamic_cast<Pawn*>(piece)) {
        if ((pawn->isWhitePiece() && row == 0) ||
            (!pawn->isWhitePiece() && row == 7)) {
            delete board[row][col];
            board[row][col] = new Queen(pawn->isWhitePiece());
        }
    }
}

bool Game::canCastle(const Position& kingPos, const Position& rookPos) {
    int row = kingPos.getRow();
    int kingCol = kingPos.getColumn();
    int rookCol = rookPos.getColumn();

    if (kingPos.getRow() != rookPos.getRow()) return false;
    if (std::abs(kingCol - rookCol) < 2) return false;

    Piece* kingPiece = board[row][kingCol];
    Piece* rookPiece = board[row][rookCol];

    if (!kingPiece || !rookPiece) return false;

    King* king = dynamic_cast<King*>(kingPiece);
    Rook* rook = dynamic_cast<Rook*>(rookPiece);

    if (!king || !rook) return false;
    if (king->hasMoved() || rook->hasMoved()) return false;
    if (king->isWhitePiece() != rook->isWhitePiece()) return false;
    if (king->isWhitePiece() != whiteTurn) return false;

    int step = (rookCol > kingCol) ? 1 : -1;
    int start = kingCol + step;
    int end = rookCol;

    for (int col = start; col != end; col += step) {
        if (board[row][col] != nullptr) {
            return false;
        }
    }

    int newKingCol = kingCol + 2 * step;
    for (int col = kingCol; col != newKingCol + step; col += step) {
        Position tempPos(row, col);
        if (moveWouldCauseCheck(kingPos, tempPos)) {
            return false;
        }
    }

    return true;
}

void Game::doCastle(const Position& kingPos, const Position& rookPos) {
    int row = kingPos.getRow();
    int kingCol = kingPos.getColumn();
    int rookCol = rookPos.getColumn();
    int step = (rookCol > kingCol) ? 1 : -1;

    King* king = dynamic_cast<King*>(board[row][kingCol]);
    board[row][kingCol + 2 * step] = king;
    board[row][kingCol] = nullptr;
    king->moved();

    Rook* rook = dynamic_cast<Rook*>(board[row][rookCol]);
    board[row][kingCol + step] = rook;
    board[row][rookCol] = nullptr;
    rook->moved();
}

bool Game::move(const Position& from, const Position& to) {
    if (gameOver || !from.isValid() || !to.isValid()) return false;

    Piece* piece = board[from.getRow()][from.getColumn()];
    if (!piece || piece->isWhitePiece() != whiteTurn) return false;

    King* king = dynamic_cast<King*>(piece);
    if (king && std::abs(from.getColumn() - to.getColumn()) == 2) {
        int rookCol = (to.getColumn() > from.getColumn()) ? 7 : 0;
        Position rookPos(from.getRow(), rookCol);

        if (canCastle(from, rookPos)) {
            doCastle(from, rookPos);
            whiteTurn = !whiteTurn;
            return true;
        }
    }

    if (!piece->canMove(from, to, board) || moveWouldCauseCheck(from, to)) {
        return false;
    }

    if (king) king->moved();
    if (Rook* rook = dynamic_cast<Rook*>(piece)) rook->moved();

    if (board[to.getRow()][to.getColumn()]) {
        delete board[to.getRow()][to.getColumn()];
    }

    board[to.getRow()][to.getColumn()] = piece;
    board[from.getRow()][from.getColumn()] = nullptr;

    promotePawnIfNeeded(to);

    if (isCheckmate(!whiteTurn)) {
        gameOver = true;
        SetConsoleTextAttribute(color, 10);
        std::wcout << (whiteTurn ? L"White" : L"Black") << L" Wins by Checkmate!" << std::endl;
        SetConsoleTextAttribute(color, 7);
    }
    else if (isStalemate(!whiteTurn)) {
        gameOver = true;
        SetConsoleTextAttribute(color, 10);
        std::wcout << L"Draw by Stalemate." << std::endl;
        SetConsoleTextAttribute(color, 7);
    }

    whiteTurn = !whiteTurn;
    return true;
}

void Game::printBoard() const {
    SetConsoleTextAttribute(color, 14);
    std::wcout << L"  a b c d e f g h" << std::endl;
    for (int r = 0; r < 8; r++) {
        std::wcout << 8 - r << L" ";
        for (int c = 0; c < 8; c++) {
            if (board[r][c]) {
                std::wcout << board[r][c]->getSymbol();
            }
            else {
                std::wcout << ((r + c) % 2 == 0 ? L"■" : L"□");
            }
            std::wcout << L" ";
        }
        std::wcout << 8 - r << std::endl;
    }
    std::wcout << L"  a b c d e f g h" << std::endl;

    SetConsoleTextAttribute(color, 7);
}

bool Game::isGameOver() const {
    return gameOver;
}

bool Game::isWhiteTurn() const {
    return whiteTurn;
}


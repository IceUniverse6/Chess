#pragma once
#include <iostream>
#include "Piece.h"
#include "Position.h"
#include "Pawn.h"
#include "Rook.h"
#include "Knight.h"
#include "Bishop.h"
#include "Queen.h"
#include "King.h"

class Game {
private:
    Piece* board[8][8];
    bool whiteTurn;
    bool gameOver;

    void setupInitialBoard();

    bool isCheck(bool);
    bool canMoveAnyPiece(bool);
    bool isCheckmate(bool);
    bool isStalemate(bool);

    bool moveWouldCauseCheck(const Position&, const Position&);

    void promotePawnIfNeeded(const Position&);
    bool canCastle(const Position&, const Position&);
    void doCastle(const Position&, const Position&);

public:
    Game();
    ~Game();

    bool move(const Position&, const Position&);
    void printBoard() const;

    bool isGameOver() const;
    bool isWhiteTurn() const;
};


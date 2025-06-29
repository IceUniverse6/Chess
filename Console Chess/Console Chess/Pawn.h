#pragma once
#include "Piece.h"
class Pawn :public Piece
{
private:

public:
	Pawn(bool);
	~Pawn() = default;

	bool canMove(const Position&, const Position&, Piece* board[8][8])const override;
	std::wstring getSymbol()const override;
};


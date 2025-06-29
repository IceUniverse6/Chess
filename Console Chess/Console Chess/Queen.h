#pragma once
#include "Piece.h"
class Queen :public Piece
{
public:
	Queen(bool);
	~Queen() = default;

	bool canMove(const Position&, const Position&, Piece* board[8][8])const override;
	std::wstring getSymbol()const override;
};


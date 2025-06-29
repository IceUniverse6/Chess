#pragma once
#include "Piece.h"
class Knight :public Piece
{
public:
	Knight(bool);
	~Knight() = default;

	bool canMove(const Position&, const Position&, Piece* board[8][8])const override;
	std::wstring getSymbol()const override;
};


#pragma once
#include "Piece.h"
class Bishop :public Piece
{
public:
	Bishop(bool);
	~Bishop() = default;

	bool canMove(const Position&, const Position&, Piece* board[8][8])const override;
	std::wstring getSymbol()const override;
};


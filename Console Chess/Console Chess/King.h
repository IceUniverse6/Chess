#pragma once
#include "Piece.h"
class King :public Piece
{
private:
	bool isMoved;
public:
	King(bool);
	~King() = default;

	bool canMove(const Position&, const Position&, Piece* board[8][8])const override;
	std::wstring getSymbol()const override;
	void moved();
	bool hasMoved()const;
};


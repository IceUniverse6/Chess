#pragma once
#include "Piece.h"
class Rook :public Piece
{
private:
	bool isMoved;
public:
	Rook(bool);
	~Rook() = default;

	bool canMove(const Position&, const Position&, Piece* board[8][8])const override;
	std::wstring getSymbol()const override;
	void moved();
	bool hasMoved()const;
};


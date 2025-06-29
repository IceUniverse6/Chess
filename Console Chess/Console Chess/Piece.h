#pragma once
#include<iostream>
#include"Position.h"
class Piece
{
protected:
	bool isWhite;
public:
	Piece(bool);
	virtual ~Piece() = default;

	bool isWhitePiece()const;
	virtual bool canMove(const Position&, const Position&, Piece* board[8][8])const = 0;
	virtual std::wstring getSymbol()const = 0;
};
#pragma once
#include<string>
class Position
{
private:
	int row;
	int column;
public:
	Position();
	Position(int, int);
	~Position();

	int getRow()const;
	int getColumn()const;

	bool isValid()const;
};


#include "Position.h"
Position::Position() : row(-1), column(-1) {}
Position::Position(int row, int column) : row(row), column(column) {}
Position::~Position() {}

int Position::getRow()const {
    return this->row;
}
int Position::getColumn()const {
    return this->column;
}

bool Position::isValid()const {
    return (this->row >= 0 && this->row < 8) && (this->column >= 0 && this->column < 8);
}

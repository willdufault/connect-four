#include "tile.hpp"

using namespace std;

Tile::Tile(int row, int col)
{
	this->row = row;
	this->col = col;
	this->piece = NULL;
}

Tile::~Tile()
{	
	delete this->piece;
}

int Tile::getRow()
{
	return this->row;
}

int Tile::getCol()
{
	return this->col;
}

Piece* Tile::getPiece()
{
	return this->piece;
}

void Tile::setTrue()
{
	this->piece = new Piece(true);
}

void Tile::setFalse()
{
	this->piece = new Piece(false);
}
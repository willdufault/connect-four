#ifndef TILE_HPP
#define TILE_HPP

#include <iostream>
#include "piece.hpp"

class Tile
{
private:
	int row;
	int col;
	Piece* piece;  // piece on this tile (NULL if no piece)
public:
	Tile(int, int);
	~Tile();
	int getRow();
	int getCol();
	Piece* getPiece();
	void setTrue();  // set piece team to true
	void setFalse();  // set piece team to false
};

#endif
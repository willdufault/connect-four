#ifndef BOARD_HPP
#define BOARD_HPP

#include <iostream>
#include <unordered_map>
#include "tile.hpp"

class Board
{
private:
	int rows;  // number of rows
	int cols;  // number of columns
	Tile** tiles;  // tiles on the board
	int* count;  // how many spots are taken in each row

public:
	Board(int, int);
	~Board();
	int getRows();
	int getCols();
	Tile** getTiles();
	int* getCount();
	void clearBoard();  // clear board
	void printBoard();  // display current board
	void printCoords();  // display coordinates of each legal position
	bool makeMove(bool, int);  // place a piece
	// these all need to be int because they can be no win, X win, 0 win
	int winHoriz();  // check for win horizontally
	int winVert();  // check for win vertically
	int winDiag1();  // check for win along first diagonal
	int winDiag2();  // check for win along second iagonal
	int checkWin();  // check for a win (includes all other win helpers)
	bool checkFull();  // check if board full
};

#endif
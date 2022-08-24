#ifndef BOT_HPP
#define BOT_HPP

#include "tile.hpp"
#include "board.hpp"

class Bot
{
private:
	bool team;
	int rows;
	int cols;
	// w = weight
	int w_2;  // 2 in a row
	int w_3;  // 3 in a row
	int w_4;  // 4 in a row, should always be 99 (or any big number)
	int w_block;  // block enemy 4 in a row
	int* scores;  // int array to store scores for each column

public:
	Bot(bool, int, int, int, int, int, int);
	~Bot();
	void setTrue();  // set team to true
	void setFalse();  // set team to false
	void resetScores();  // sets all values in scores to 0
	void getScores(Tile**, int*);  // get scores for each possible move
	int botMove();  // make move based on best score
};

#endif
#include "board.hpp"

using namespace std;

Board::Board(int rows, int cols)
{
	this->rows = rows;
	this->cols = cols;
	this->tiles = (Tile**) malloc(rows * cols * sizeof(Tile*));
	for(int r = 0; r < this->rows; r++)
	{  // initialize values
		for(int c = 0; c < this->cols; c++)
		{
			*(this->tiles + (r * this->cols) + c) = new Tile(r, c);
		}
	}
	this->count = (int*) malloc(cols * sizeof(int));  // how many pieces places in each col
	for(int i = 0; i < cols; i++)
	{  // initialize values
		*(count + i) = 0;
	}
}

Board::~Board()
{
	for(int r = 0; r < this->rows; r++)
	{  // delete all tiles
		for(int c = 0; c < this->cols; c++)
		{
			delete *(this->tiles + (r * this->cols) + c);
		}
	}
	free(this->tiles);
	free(this->count);
}

int Board::getRows()
{
	return this->rows;
}

int Board::getCols()
{
	return this->cols;
}

Tile** Board::getTiles()
{
	return this->tiles;
}

int* Board::getCount()
{
	return this->count;
}

void Board::clearBoard()
{
	for(int r = 0; r < this->rows; r++)
	{  // clear all pieces
		for(int c = 0; c < this->cols; c++)
		{
			delete *(this->tiles + (r * this->cols) + c);
			*(this->tiles + (r * this->cols) + c) = new Tile(r, c);
		}
	}
	for(int i = 0; i < cols; i++)
	{  // reset counts
		*(count + i) = 0;
	}
}

void Board::printBoard()
{
	for(int r = (this->rows - 1); r > -1; r--)
	{  // so bottom left is (0, 0)
		for(int c = 0; c < this->cols; c++)
		{
			cout << "| ";
			Piece* currPiece = (*(this->tiles + (r * this->cols) + c))->getPiece();
			if(currPiece != NULL)
			{
				if(currPiece->getTeam())
				{  // true is X
					cout << "X ";
				} else
				{  // false is O
					cout << "O ";
				}
			} else
			{
				cout << "  ";
			}
		}
		cout << "|" << endl;
	}
	cout << endl;
}

void Board::printCoords()
{
	for(int r = (this->rows - 1); r > -1; r--)
	{
		for(int c = 0; c < this->cols; c++)
		{
			cout << "|" << r << c;	
		}
		cout << "|" << endl;
	}
}

bool Board::makeMove(bool team, int col)
{
	if((col < 0) || (col >= this->cols) || (this->count[col] >= this->rows))
	{  // if out of bounds or column full
		return false;
	}
	// put piece in this column
	if(team)
	{
		(*(tiles + (this->count[col]++ * this->cols) + col))->setTrue();
	} else
	{
		(*(tiles + (this->count[col]++ * this->cols) + col))->setFalse();
	}
	return true;
}

int Board::winHoriz()
{
	int streak = 0;
	bool team = false;
	for(int r = 0; r < this->rows; r++)
	{
		for(int c = 0; c < this->cols; c++)
		{
			if(r >= this->count[c])
			{  // if row number is higher than the amount of pieces in this column
				streak = 0;
				continue;
			}
			bool currTeam = (*(this->tiles + (r * this->cols) + c))->getPiece()->getTeam();
			if(streak == 0)
			{
				team = currTeam;
				streak++;
			} else if(team == currTeam)
			{
				streak++;	
			} else
			{
				streak = 1;
				team = !team;
			}
			if(streak == 4)
			{
				return (team ? 1 : 0);
			}
		}
		// reset streak for new row
		streak = 0;
	}
	return -1;
}

int Board::winVert()
{
	int streak = 0;
	bool team = false;
	for(int c = 0; c < this->cols; c++)
	{
		for(int r = 0; r < this->rows; r++)
		{
			if(r >= this->count[c])
			{  // if row number is higher than the amount of pieces in this column
				streak = 0;
				continue;
			}
			bool currTeam = (*(this->tiles + (r * this->cols) + c))->getPiece()->getTeam();
			if(streak == 0)
			{
				team = currTeam;
				streak++;
			} else if(team == currTeam)
			{
				streak++;	
			} else
			{
				streak = 1;
				team = !team;
			}
			if(streak == 4)
			{
				return (team ? 1 : 0);
			}
		}
		// reset streak for new column
		streak = 0;
	}
	return -1;
}

int Board::winDiag1()
{
	unordered_map<int, bool> cache;  // better for larger boards
	for(int r = 0; r < this->rows; r++)
	{
		for(int c = 0; c < this->cols; c++)
		{
			if(c > 2)
			{  // need to be at least 3 cols in
				int r1 = r;
				int c1 = c;
				int streak = 0;
				bool team = false;
				while(r1 < this->count[c1])
				{  // while there is a piece here
					int key = ((r1 * this->cols) + c1);
					bool currTeam = (*(this->tiles + key))->getPiece()->getTeam();
					if(streak == 0)
					{
						team = currTeam;
					} else if(team != currTeam)
					{
						break;
					}
					// streak continues
					if(cache.find(key) == cache.end())
					{  // insert into cache
						cache.insert(make_pair(key, true));
					} else
					{  // we've already checked this tile
						break;
					}
					streak++;
					r1++;
					c1--;
					if(streak == 4)
					{
						return (team ? 1 : 0);
					}
				}
			}
		}
	}
	// clear cache, good practice
	cache.clear();
	return -1;
}

int Board::winDiag2()
{
	unordered_map<int, bool> cache;  // better for larger boards
	for(int r = 0; r < this->rows; r++)
	{
		for(int c = 0; c < this->cols; c++)
		{
			if(c < (this->cols - 3))
			{  // need to be at least 3 cols in
				int r1 = r;
				int c1 = c;
				int streak = 0;
				bool team = false;
				while(r1 < this->count[c1])
				{  // while there is a piece here
					int key = ((r1 * this->cols) + c1);
					bool currTeam = (*(this->tiles + key))->getPiece()->getTeam();
					if(streak == 0)
					{
						team = currTeam;
					} else if(team != currTeam)
					{
						break;
					}
					// streak continues
					if(cache.find(key) == cache.end())
					{  // insert into cache
						cache.insert(make_pair(key, true));
					} else
					{  // we've already checked this one
						break;
					}
					streak++;
					r1++;
					c1++;
					if(streak == 4)
					{
						return (team ? 1 : 0);
					}
				}
			}
		}
	}
	// clear cache, good practice
	cache.clear();
	return -1;
}

// todo: optimize all helpers so we only check if the new pieces make a win, no need to keep checking old pieces
int Board::checkWin()
{
	int h = winHoriz();
	if(h != -1)
	{
		return h;
	}
	int v = winVert();
	if(v != -1)
	{
		return v;
	}
	int d1 = winDiag1();
	if(d1 != -1)
	{
		return d1;
	}
	int d2 = winDiag2();
	if(d2 != -1)
	{
		return d2;
	}
	return -1;  // -1 = no win, 0 = false win, 1 = true win
}

bool Board::checkFull()
{
	for(int i = 0; i < this->cols; i++)
	{
		if(this->count[i] != this->rows)
		{
			return false;
		}
	}
	return true;
}
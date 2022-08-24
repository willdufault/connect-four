#include "bot.hpp"

using namespace std;

Bot::Bot(bool team, int rows, int cols, int w_2, int w_3, int w_4, int w_block)
{
	this->team = team;
	this->rows = rows;
	this->cols = cols;
	this->w_2 = w_2;
	this->w_3 = w_3;
	this->w_4 = w_4;
	this->w_block = w_block;
	this->scores = (int*) malloc(cols * sizeof(int));
	this->vals = (int*) malloc(cols * sizeof(int));
	resetScores();  // initialize scores
	resetVals();  // initialize vals
}

Bot::~Bot()
{
	free(this->scores);
	free(this->vals);
}

void Bot::setTrue()
{
	this->team = true;
}

void Bot::setFalse()
{
	this->team = false;
}

void Bot::resetScores()
{
	for(int i = 0; i <this->cols; i++)
	{  // reset all scores
		*(this->scores + i) = 0;
	}
}

void Bot::resetVals()
{
	for(int i = 0; i < this->cols; i++)
	{  // reset all vals
		*(vals + i) = 0;
	}
}

// todo: add a helper to decrease repetition

/*
take tiles as input, make judgement based on board it receives
*/
void Bot::getScores(Tile** tiles, int* count)
{
	resetScores();
	for(int c = 0; c < this->cols; c++)
	{  // for every column
		int r = *(count + c);  // get legal move in this column
		if(r == this->rows)
		{  // this column is full, don't go here, next column
			*(this->scores + c) = INT_MIN;
			continue;
		}
		// legal position found
		// check down
		bool tracking = false;  // value of team being tracked (true for bot team, false for opponent team)
		int streak = 0;  // how many pieces in a row (not counting new piece)
		int opp_streak = 0;  // how many opponent pieces in a row
		int r1 = r;  // copy of r
		int c1 = c;  // copy of c
		if(--r1 > -1)
		{  // if in bounds
			// don't need to check for null going down
			Piece* next = (*(tiles + (r1 * this->cols) + c1))->getPiece();
			bool next_team = next->getTeam();
			tracking = ((next_team == team) ? true : false);  // team we're tracking in this direction
			// increment the streak in this direction
			if(tracking)
			{
				streak++;
			} else
			{
				opp_streak++;
			}
			while(--r1 > -1)
			{  // while streak continues
				next = (*(tiles + (r1 * this->cols) + c1))->getPiece();
				// don't need to check for null going down
				next_team = next->getTeam();
				if(tracking && (next_team == team))
				{  // streak continues
					streak++;
				} else if(!tracking && (next_team != team))
				{  // streak continues
					opp_streak++;
				} else
				{
					break;
				}
			}
		}
		*(this->scores + c) += (((streak == 1) ? this->w_2 : 0) + ((streak == 2) ? this->w_3 : 0) + ((streak == 3) ? this->w_4 : 0) + ((opp_streak == 3) ? this->w_block : 0));
		// check left
		streak = 0;
		opp_streak = 0;
		r1 = r;
		c1 = c;
		if(--c1 > -1)
		{  // if in bounds
			Piece* next = (*(tiles + (r1 * this->cols) + c1))->getPiece();
			if(next != NULL)
			{  // piece exists
				bool next_team = next->getTeam();
				tracking = ((next_team == team) ? true : false);  // team we're tracking in this direction
				// increment the streak in this direction
				if(tracking)
				{
					streak++;
				} else
				{
					opp_streak++;
				}
				while(--c1 > -1)
				{  // while streak continues
					next = (*(tiles + (r1 * this->cols) + c1))->getPiece();
					if(next != NULL)
					{  // piece exists
						next_team = next->getTeam();
						if(tracking && (next_team == team))
						{  // streak continues
							streak++;
						} else if(!tracking && (next_team != team))
						{  // streak continues
							opp_streak++;
						} else
						{  // streak broken
							break;
						}
					} else
					{  // no piece
						break;
					}
				}
			}
		}
		// check right
		r1 = r;
		c1 = c;
		if(++c1 < this->cols)
		{  // if in bounds
			Piece* next = (*(tiles + (r1 * this->cols) + c1))->getPiece();
			if(next != NULL)
			{  // piece exists
				bool next_team = next->getTeam();
				tracking = ((next_team == team) ? true : false);  // team we're tracking in this direction
				// increment the streak in this direction
				if(tracking)
				{
					streak++;
				} else
				{
					opp_streak++;
				}
				while(++c1 < this->cols)
				{  // while streak continues
					next = (*(tiles + (r1 * this->cols) + c1))->getPiece();
					if(next != NULL)
					{  // piece exists
						next_team = next->getTeam();
						if(tracking && (next_team == team))
						{  // streak continues
							streak++;
						} else if(!tracking && (next_team != team))
						{  // streak continues
							opp_streak++;
						} else
						{  // streak broken
							break;
						}
					} else
					{  // no piece
						break;
					}
				}
			}
		}
		*(this->scores + c) += (((streak == 1) ? this->w_2 : 0) + ((streak == 2) ? this->w_3 : 0) + ((streak == 3) ? this->w_4 : 0) + ((opp_streak == 3) ? this->w_block : 0));
		// check up left
		streak = 0;
		opp_streak = 0;
		r1 = r;
		c1 = c;
		if((++r1 < this->rows) && (--c1 > -1))
		{  // if in bounds
			Piece* next = (*(tiles + (r1 * this->cols) + c1))->getPiece();
			if(next != NULL)
			{  // piece exists
				bool next_team = next->getTeam();
				tracking = ((next_team == team) ? true : false);  // team we're tracking in this direction
				// increment the streak in this direction
				if(tracking)
				{
					streak++;
				} else
				{
					opp_streak++;
				}
				while((++r1 < this->rows) && (--c1 > -1))
				{  // while streak continues
					next = (*(tiles + (r1 * this->cols) + c1))->getPiece();
					if(next != NULL)
					{  // piece exists
						next_team = next->getTeam();
						if(tracking && (next_team == team))
						{  // streak continues
							streak++;
						} else if(!tracking && (next_team != team))
						{  // streak continues
							opp_streak++;
						} else
						{  // streak broken
							break;
						}
					} else
					{  // no piece
						break;
					}
				}
			}
		}
		// check down right
		r1 = r;
		c1 = c;
		if((--r1 > -1) && (++c1 < this->cols))
		{  // if in bounds
			Piece* next = (*(tiles + (r1 * this->cols) + c1))->getPiece();
			if(next != NULL)
			{  // piece exists
				bool next_team = next->getTeam();
				tracking = ((next_team == team) ? true : false);  // team we're tracking in this direction
				// increment the streak in this direction
				if(tracking)
				{
					streak++;
				} else
				{
					opp_streak++;
				}
				while((--r1 > -1) && (++c1 < this->cols))
				{  // while streak continues
					next = (*(tiles + (r1 * this->cols) + c1))->getPiece();
					if(next != NULL)
					{  // piece exists
						next_team = next->getTeam();
						if(tracking && (next_team == team))
						{  // streak continues
							streak++;
						} else if(!tracking && (next_team != team))
						{  // streak continues
							opp_streak++;
						} else
						{  // streak broken
							break;
						}
					} else
					{  // no piece
						break;
					}
				}
			}
		}
		*(this->scores + c) += (((streak == 1) ? this->w_2 : 0) + ((streak == 2) ? this->w_3 : 0) + ((streak == 3) ? this->w_4 : 0) + ((opp_streak == 3) ? this->w_block : 0));
		// check down left
		streak = 0;
		opp_streak = 0;
		r1 = r;
		c1 = c;
		if((--r1 > -1) && (--c1 > -1))
		{  // if in bounds
			Piece* next = (*(tiles + (r1 * this->cols) + c1))->getPiece();
			if(next != NULL)
			{  // piece exists
				bool next_team = next->getTeam();
				tracking = ((next_team == team) ? true : false);  // team we're tracking in this direction
				// increment the streak in this direction
				if(tracking)
				{
					streak++;
				} else
				{
					opp_streak++;
				}
				while((--r1 > -1) && (--c1 > -1))
				{  // while streak continues
					next = (*(tiles + (r1 * this->cols) + c1))->getPiece();
					if(next != NULL)
					{  // piece exists
						next_team = next->getTeam();
						if(tracking && (next_team == team))
						{  // streak continues
							streak++;
						} else if(!tracking && (next_team != team))
						{  // streak continues
							opp_streak++;
						} else
						{  // streak broken
							break;
						}
					} else
					{  // no piece
						break;
					}
				}
			}
		}
		// check up right
		r1 = r;
		c1 = c;
		if((++r1 < this->rows) && (++c1 < this->cols))
		{  // if in bounds
			Piece* next = (*(tiles + (r1 * this->cols) + c1))->getPiece();
			if(next != NULL)
			{  // piece exists
				bool next_team = next->getTeam();
				tracking = ((next_team == team) ? true : false);  // team we're tracking in this direction
				// increment the streak in this direction
				if(tracking)
				{
					streak++;
				} else
				{
					opp_streak++;
				}
				while((++r1 < this->rows) && (++c1 < this->cols))
				{  // while streak continues
					next = (*(tiles + (r1 * this->cols) + c1))->getPiece();
					if(next != NULL)
					{  // piece exists
						next_team = next->getTeam();
						if(tracking && (next_team == team))
						{  // streak continues
							streak++;
						} else if(!tracking && (next_team != team))
						{  // streak continues
							opp_streak++;
						} else
						{  // streak broken
							break;
						}
					} else
					{  // no piece
						break;
					}
				}
			}
		}
		*(this->scores + c) += (((streak == 1) ? this->w_2 : 0) + ((streak == 2) ? this->w_3 : 0) + ((streak == 3) ? this->w_4 : 0) + ((opp_streak == 3) ? this->w_block : 0));
	}
}

int Bot::botMove()
{
	resetVals();
	int idx = 0;  // current index for vals
	// find highest score(s)
	// cout << "scores: ";
	for(int i = 0; i < this->cols; i++)
	{
		int score = *(this->scores + i);
		// cout << score << " ";
		int val = *(this->scores + *vals);
		if(score > val)
		{
			// set first val to column of new high
			*vals = i;
			// reset other vals
			for(int i = 1; i < this->cols; i++)
			{
				*(vals + i) = 0;
			}
			idx = 0;
		} else if(score == val)
		{
			*(vals + ++idx) = i;
		}
	}
	cout << endl;
	// pick random column from scores
	srand(time(NULL));  // ensure rand() is not pseudo-random
	// cout << "vals: ";
	int ans = ((idx > 0) ? *(vals + (rand() % idx)) : *vals);
	return ans;
}
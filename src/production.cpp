#include "production.hpp"

using namespace std;

Production::Production()
{}

void Production::runProduction()
{
	cout << endl;  // prettier
	// initialize board, default size is 6 rows by 7 columns
	int rows = 6;
	int cols = 7;
	Board* board = new Board(rows, cols);
	// initialize variables for game
	bool team = true;
	bool again = true;
	int win = -1;
	bool full = false;
	int in_int = 0;  // for cin
	string in_str;  // for cin
	// initialize bot, can change weights to change bot behavior
	Bot* bot = new Bot(true, rows, cols, 4, 9, 9999, 25);  // args: team, rows, cols, w_2, w_3, w_4 (win), w_block
	while(true)
	{  // game loop
		while(true)
		{  // choose game mode
			cout << "would you like to play against a bot (1) or another person (2) ?" << endl;
			cin >> in_int;
			if((in_int == 1) || (in_int == 2))
			{
				break;
			}
			cout << "error reading input. ";
			cin.clear();
			cin.ignore(INT_MAX, '\n');
		}
		cin.clear();
		cin.ignore(INT_MAX, '\n');
		cout << endl;  // prettier
		if(in_int == 1)
		{  // play against bot
			while(true)
			{  // choose team
				cout << "would you like to go first? (y/n)" << endl;
				cin >> in_str;
				if(in_str == "y")
				{  // assign teams
					team = true;
					bot->setFalse();
					break;
				} else if(in_str == "n")
				{  // assign teams
					team = false;
					bot->setTrue();
					break;
				}
				cout << "error reading input. ";
				cin.clear();
				cin.ignore(INT_MAX, '\n');
			}
			cin.clear();
			cin.ignore(INT_MAX, '\n');
			cout << endl;
			if(!team)
			{  // if player goes second
				bot->getScores(board->getTiles(), board->getCount());
				int bot_move = bot->botMove();
				board->makeMove(!team, bot_move);
				cout << "bot (team " << (!team ? "X" : "O") << ") placed a piece in column " << (bot_move + 1) << endl << endl;
			}
			while(again)
			{  // play loop
				board->printBoard();
				while(true)
				{  // player enters valid move
					cout << "team " << (team ? "X" : "O") << ", pick a column (1 - " << cols << ")." << endl;
					cin >> in_int;
					if(in_int == 0)
					{
						return;
					} else if((in_int > 0) && (in_int <= cols))
					{
						in_int--;
						if(board->makeMove(team, in_int))
						{
							break;
						}
					}
					cout << "error reading input. ";
					cin.clear();
					cin.ignore(INT_MAX, '\n');
				}
				cout << endl;
				win = board->checkWin();
				full = board->checkFull();
				again = ((win == -1) && !full);
				if(!again)
				{
					break;
				}
				board->printBoard();
				// bot moves
				bot->getScores(board->getTiles(), board->getCount());
				int bot_move = bot->botMove();
				board->makeMove(!team, bot_move);
				cout << "bot (team " << (!team ? "X" : "O") << ") placed a piece in column " << (bot_move + 1) << endl << endl; // prettier
				win = board->checkWin();
				full = board->checkFull();
				again = ((win == -1) && !full);
			}
		} else
		{  // play against human
			while(again)
			{
				board->printBoard();
				while(true)
				{  // enter valid move
					cout << "team " << (team ? "X" : "O") << ", pick a column (1 - " << cols << ")." << endl;
					cin >> in_int;
					if(in_int == 0)
					{
						return;
					} else if((in_int > 0) && (in_int <= cols))
					{
						in_int--;
						if(board->makeMove(team, in_int))
						{
							break;
						}
					}
					cout << "error reading input. ";
					cin.clear();
					cin.ignore(INT_MAX, '\n');
				}
				cout << endl;
				win = board->checkWin();
				full = board->checkFull();
				again = ((win == -1) && !full);
				team = !team;
			}
		}
		board->printBoard();
		if(win == 0)
		{
			cout << "team O wins!" << endl;
		} else if(win == 1)
		{
			cout << "team X wins!" << endl;
		} else if(full)
		{
			cout << "board is full. it's a draw." << endl;
		}
		cout << endl;  // prettier
		while(true)
		{  // play again loop
			cout << "play again? (y/n)" << endl;
			cin >> in_str;
			if(in_str == "y")
			{
				break;
			} else if(in_str == "n")
			{
				return;
			}
			cout << "error reading input. ";
			cin.clear();
			cin.ignore(INT_MAX, '\n');
		}
		board->clearBoard();
		team = true;
		again = true;
		win = -1;
		full = false;
		cout << endl;  // prettier
	}
	delete board;
	delete bot;
}
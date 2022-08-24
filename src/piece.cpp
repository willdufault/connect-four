#include "piece.hpp"

using namespace std;

Piece::Piece(bool team)
{
	this->team = team;
}

bool Piece::getTeam()
{
	return this->team;
}

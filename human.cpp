#include "human.h"
#include <string>

Move translate(istream& humanMove) {
	string piece;
	string startRank;
	string startFile;
	string endRank;
	string endFile;
	humanMove >> piece >> startFile >> startRank >> endFile >> endRank;
	Move movie;
	movie.finalx = int8_t(endFile[0] - 'a');
	movie.finaly = stoi(endRank) - 8;
	movie.startx = int8_t(startFile[0] - 'a');
	movie.starty = stoi(startRank) - 8;
	if (piece[0] >= 97)
		movie.pieceType = piece[0] - 32;
	else
		movie.pieceType = piece[0];
	return movie;
}
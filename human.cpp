#include "human.h"
#include <string>
#include <iostream>

Move translate() {
	string piece;
	string startRank;
	string startFile;
	string endRank;
	string endFile;
	std::cout << "Please enter a move: ";
	std::cin >> piece >> startFile >> startRank >> endFile >> endRank;
	Move movie;
	movie.finalx = int8_t(endFile[0] - 'a');
	movie.finaly = 8 - stoi(endRank);
	movie.startx = int8_t(startFile[0] - 'a');
	movie.starty = 8 - stoi(startRank);
	if (piece[0] >= 97)
		movie.pieceType = piece[0] - 32;
	else
		movie.pieceType = piece[0];
	return movie;
}
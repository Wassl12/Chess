#pragma once
#include "pieces.h"


struct Move {
	int8_t finaly;
	int8_t finalx;
	int8_t starty;
	int8_t startx;
	char pieceType;

};

bool swapBoards(Board& board, Move& mov);
void moveMaker(Board& board, vector <Move>& moves, char color);
void bestChoice(int searchDepth);
void boardSwapper(int searchDepth, int depth, vector<Piece*>& swapBuffer);
void verify(Board& board, vector <Move>& moves);

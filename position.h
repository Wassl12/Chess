#pragma once

#include "pieces.h"
// look for things in board and check for penalties and reductions 
double position(Board& board, int turn, char whoseMove);
bool hanging(string pieceType, Board& board, int turn, char whoseMove);

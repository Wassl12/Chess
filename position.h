#pragma once

#include "pieces.h"
// look for things in board and check for penalties and reductions 
double position(Board& board, int turn, char whoseMove, bool &hang);
bool hanging(string pieceType, Board& board, int turn, char whoseMove);
void moveBonuses(Board& board, double &score, string piece, const double bonus, char color, double trappedPenalty);
bool anythingHanging(Board& board, char whoseMove);
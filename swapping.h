#pragma once
#include "verification.h"




double boardSwapper(Board& board, int searchDepth, int depth, vector<Piece*>& swapBuffer, vector<Move>& moveBuffer, int turn, double alpha, double beta);

void bestChoice(Board& board, int searchDepth, char color, int turn);

bool worthwhile(double immediatePos, double currentBest, char thisColor);
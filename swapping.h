#pragma once


double boardSwapper(Board& board, int searchDepth, int depth, vector<Piece*>& swapBuffer, vector<Move>& moveBuffer, long int color, double value);

void bestChoice(int searchDepth);

bool worthwhile(double immediatePos, double currentBest, char thisColor, double k);
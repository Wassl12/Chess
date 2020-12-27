#pragma once

double k = 1;
int moveschecked = 0;
int movesCut = 0;


double boardSwapper(Board& board, int searchDepth, int depth, vector<Piece*>& swapBuffer, vector<Move>& moveBuffer, long int color, double value);

void bestChoice(Board &board, int searchDepth);

bool worthwhile(double immediatePos, double currentBest, char thisColor, double k);
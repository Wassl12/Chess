#include "pieces.h"
#include "position.h"
#include <algorithm>

using namespace std;

double position(Board &board, int turn, char whoseMove) {
	/*    x = 0		1		2		3		4		5		6		7
	y = 0
	y = 1	bp		bp		bp		bp
	y = 2
	y = 3
	y = 4
	y = 5
	y = 6
	y = 7
	*/

	// a score that tells which color has an advantage currently.
	// negative means black is in favor and positive means white is in favor



	// pawn worth +- 1 penalties/bonuses
	// bishop knight worth +- 3
	// Queen worth +- 9
	// Rook worth +- 5
	// king worth +- 1000000000
	/* things to look for:
		if queen is threatened, penalty
		if rook is threatened, penalty
		if pawn is blocked, penalty
		if piece is in an outpost, bonus
		if pawn has an open file, big bonus
		if knight is near center, big bonus
		if both bishops are alive, extra bonus
		if rook is trapped, penalty
		if game is late, pawn bonus
		if game is early, pawn penalty

	*/

	double score = 0;
	char defendingColor = 'b';
	double sign = 1;
	if (whoseMove == 'b')
		sign = -1;
	if (whoseMove == defendingColor)
		defendingColor = 'w';

	// add piece value
	for (auto vec : board.whitePieceMap) {
		for (int8_t index = 0; index < vec.second.size(); index++ ) {
			score += vec.second[index]->value;
		}
	}

	for (auto vec : board.blackPieceMap) {

		for (int8_t index = 0; index < vec.second.size(); index++ ) {
			score -= vec.second[index]->value;
		}


	}
	

	if (hanging("Queen",board, turn, whoseMove) != 0) {
		score += 9 * sign;
			
	}
	else if (hanging("Rook",board, turn, whoseMove)) {
		score += 5 * sign;
	}

	else if (hanging("Bishop",board, turn, whoseMove)) {
		score += 3 * sign;
	}
	else if (hanging("Knight",board, turn, whoseMove)) {
		score += 3 * sign;
	}
	
	

	

}
bool hanging(string pieceType,Board &board, int turn, char whoseMove) {

	if (whoseMove == 'w') {
		
		for (int i = 0; i < board.blackPieceMap[pieceType].size(); i++) {
			int8_t pieceX = board.blackPieceMap[pieceType][i]->x;
			int8_t pieceY = board.blackPieceMap[pieceType][i]->y;
			if (board.threatened(pieceX, pieceY, 'b')) {
				return true;
			}
			
		}
	}
	else {
		for (int i = 0; i < board.whitePieceMap[pieceType].size(); i++) {
			int8_t pieceX = board.whitePieceMap[pieceType][i]->x;
			int8_t pieceY = board.whitePieceMap[pieceType][i]->y;
			if (board.threatened(pieceX, pieceY, 'w')) {
				return true;
			}
			
		}
	}
	return false;
}


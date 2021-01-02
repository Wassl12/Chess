#include "pieces.h"
#include "position.h"
#include <algorithm>
#include <iostream>
#include "verification.h"

using namespace std;

double position(Board &board, int turn, char whoseMove, bool &hang) {
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
		if queen is threatened, penalty -- done
		if rook is threatened, penalty -- done
		if pawn is blocked, penalty -- done
		if piece is in an outpost, bonus
		if pawn has an open file, big bonus
		if knight is near center, big bonus
		if both bishops are alive, extra bonus
		if rook is trapped, penalty
		if game is late, pawn bonus
		if game is early, pawn penalty

	*/

	const double earlyPenalty = -.1;
	const double blockedPawnPenalty = -.2;
	const double rookMoveValue = .05;
	const double queenMoveValue = 0.1;
	const double bishopMoveValue = 0.03;
	const double knightMoveValue = 0.02;
	const double outpostValue = 0.5;
	const double bishopsAliveValue = 1.0;
	const double rookTrapped = -1.2;
	const double bishopTrapped = -0.7;
	const double QueenTrapped = -1.5;
	const double knightTrapped = -0.5;
	

	double score = 0;
	char defendingColor = 'b';
	double sign = 1;
	if (whoseMove == 'b')
		sign = -1;
	if (whoseMove == defendingColor)
		defendingColor = 'w';

	// add piece value
	for (auto vec : board.whitePieceMap) {
		for (int8_t index = 0; index < int8_t(vec.second.size()); index++ ) {
			score += vec.second[index]->value;
		}
	}

	for (auto vec : board.blackPieceMap) {

		for (int8_t index = 0; index < int8_t(vec.second.size()); index++ ) {
			score -= vec.second[index]->value;
		}


	}
	
	// HANGING//
	
	if (hanging("Queen",board, turn, whoseMove) != 0) {
		score += 9 * sign;
		hang = true;
	}
	else if (hanging("Rook",board, turn, whoseMove)) {
		score += 5 * sign;
		hang = true;
	}

	else if (hanging("Bishop",board, turn, whoseMove)) {
		score += 3 * sign;
		hang = true;
	}
	else if (hanging("Knight",board, turn, whoseMove)) {
		score += 3 * sign;
		hang = true;
	}
	// HANGING//

	// PAWN PENALTIES//
	if (turn < 16) {
		score -= board.whitePieceMap["Pawn"].size() * earlyPenalty;
		score += board.blackPieceMap["Pawn"].size() * earlyPenalty;
	}
	if (turn > 50) {
		score += board.whitePieceMap["Pawn"].size() * earlyPenalty;
		score -= board.blackPieceMap["Pawn"].size() * earlyPenalty;
	}
	
	for (auto it = board.whitePieceMap["Pawn"].begin(); it != board.whitePieceMap["Pawn"].end(); it++) {
		if (board.blockedPawn(*it))
			score -= blockedPawnPenalty;
	}
	for (auto it = board.blackPieceMap["Pawn"].begin(); it != board.blackPieceMap["Pawn"].end(); it++) {
		if (board.blockedPawn(*it))
			score += blockedPawnPenalty;
	}
	// PAWN PENALTIES// 

	// MOVE BONUSES //
	moveBonuses(board, score, "Queen",queenMoveValue,'b' ,QueenTrapped);
	moveBonuses(board, score, "Queen", queenMoveValue, 'w',QueenTrapped);
	moveBonuses(board, score, "Rook",rookMoveValue,'b',rookTrapped);
	moveBonuses(board, score, "Rook", rookMoveValue, 'w',rookTrapped);
	moveBonuses(board, score, "Bishop", bishopMoveValue, 'b',bishopTrapped);
	moveBonuses(board, score, "Bishop", bishopMoveValue, 'w',bishopTrapped);
	moveBonuses(board, score, "Knight", knightMoveValue, 'b',knightTrapped);
	moveBonuses(board, score, "Knight", knightMoveValue, 'w',knightTrapped);
	// MOVE BONUSES

	// BISHOPS ALIVE//
	if (board.whitePieceMap["Bishop"].size() == 2)
		score += bishopsAliveValue;
	if (board.blackPieceMap["Bishop"].size() == 2)
		score -= bishopsAliveValue;
	// BISHOPS ALIVE //

	
	


	std::cout << "Score at this leaf node: " << score << '\n';
	return score;

}
bool hanging(string pieceType,Board &board, int turn, char whoseMove) {

	if (whoseMove == 'w') {
		
		for (unsigned int i = 0; i < board.blackPieceMap[pieceType].size(); i++) {
			int8_t pieceX = board.blackPieceMap[pieceType][i]->x;
			int8_t pieceY = board.blackPieceMap[pieceType][i]->y;
			if (board.threatened(pieceX, pieceY, 'b') && !board.threatened(pieceX, pieceY, 'w')) {
				return true;
			}
			
		}
	}
	else {
		for (unsigned int i = 0; i < board.whitePieceMap[pieceType].size(); i++) {
			int8_t pieceX = board.whitePieceMap[pieceType][i]->x;
			int8_t pieceY = board.whitePieceMap[pieceType][i]->y;
			if (board.threatened(pieceX, pieceY, 'w') && !board.threatened(pieceX, pieceY, 'b')) {
				return true;
			}
			
		}
	}
	return false;
}

bool Board::blockedPawn(Piece* piece) {
	char color = piece->color;
	if (color == 'b') {
		if (arr[piece->x][piece->y + 1]->type != 'E' && (piece->x == 7 || arr[piece->x + 1][piece->y + 1]->color != 'w') && (piece->x == 0 || arr[piece->x - 1][piece->y + 1]->color != 'w'))
			return true;
	}
	else {

		if (arr[piece->x][piece->y - 1]->type != 'E' && (piece->x == 7 || arr[piece->x + 1][piece->y - 1]->color != 'b') && (piece->x == 0 || arr[piece->x - 1][piece->y - 1]->color != 'b'))
			return true;

	}
	return false;
}

void moveBonuses(Board& board, double &score, string piece, const double bonus, char color, double trappedPenalty) {
	if (color == 'b') {
		for (auto it = board.blackPieceMap[piece].begin(); it != board.blackPieceMap[piece].end(); ++it) {
			vector <pair <int8_t, int8_t > > moves;
			(*it)->move(board, moves);
			score -= moves.size() * bonus;
			if (moves.size() == 0)
				score += trappedPenalty;
		}
	}
	else {
		for (auto it = board.whitePieceMap[piece].begin(); it != board.whitePieceMap[piece].end(); ++it) {
			vector <pair <int8_t, int8_t > > moves;
			(*it)->move(board, moves);
			score += moves.size() * bonus;
			if (moves.size() == 0)
				score -= trappedPenalty;
		}
	}


}

/*double tradeResults(Board& board, int turn, char firstMove, int8_t x, int8_t y) {// to prevent the hanging thing from ruining the evaluation function

	// creates a tree to resolve hanging pieces
	double result = hangPosition(board, firstMove, x, y); // ANOTHER minimax tree



}

double hangPosition(Board& board,int turn, char whoseMove, int8_t x, int8_t y) {// something is hanging which makes the board hard to evaluate

	if (!anythingHanging(board, whoseMove)) {
		return position(board, turn, whoseMove);
	}
	vector<Move> moves;
	moveMaker(board, moves, whoseMove);
	auto it = remove_if(moves.begin(), moves.end(), [&](Move& move) {return swapBoards(board, move); });
	moves.erase(it, moves.end());
	it = remove_if(moves.begin(), moves.end(), [&](Move& move) {return (move.finalx != x || move.finaly != y); });
	moves.erase(it, moves.end());
	for(int i = 0; i < )

}*/
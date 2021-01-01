#include "verification.h"
#include "position.h"
#include "swapping.h"

double k = 1;
int moveschecked = 0;
int movesCut = 0;

double boardSwapper(Board& board, int searchDepth, int depth, vector<Piece*>& swapBuffer, vector<Move>& moveBuffer, int color, double value, int turn, double alpha, double beta) {// this will swap
	// if color is odd, black
	// if color is even, white
	char col = 'b';
	if (color % 2 == 0)
		col = 'w';
	if (depth == searchDepth) {
		return position(board,turn,col);
	}


	vector <Move> moves;
	moveMaker(board, moves, col);
	// now moves is full of different moves
	double threshold = 1000000000;
	if (color % 2 == 0)// if white
		threshold *= -1;
	double result = 0;
	bool firstPass = true;
	for (unsigned int i = 0; i < moves.size(); i++) {
		// two values at each point
		// immediate position -- can be calculated up front
		// leaf position -- this is the most optimal of all the leaf nodes

		// SWAP
		Piece* temp = board.arr[moves[i].starty][moves[i].startx];
		board.arr[moves[i].starty][moves[i].startx] = swapBuffer[depth];
		swapBuffer[depth] = board.arr[moves[i].finaly][moves[i].finalx];//captured piece
		// SWAP

		if (beta <= alpha)
			return result;
		if (firstPass || worthwhile(position(board,turn,col), result,color)) {
			moveschecked++;
			result = boardSwapper(board, searchDepth, depth + 1, swapBuffer, moveBuffer, color + 1, value, turn+1,alpha,beta);
			firstPass = false;
		}
		else {
			movesCut++; // DIAGNOSTICS
		}
		if (color % 2 == 1 && result < beta)// black edits the beta value
			beta = result; // For black
		if (color % 2 == 0 && result > alpha)
			alpha = result; // For white
		if (color % 2 == 1 && result < threshold){// search for a minimum value
			moveBuffer[depth] = moves[i]; // black attempts to minimize value
			threshold = result;
			
		}
			
		else if (color % 2 == 0 && result > threshold) {
			moveBuffer[depth] = moves[i]; // white attempts to maximize
			threshold = result;
		}
			


		// unswap
		Piece* empty = swapBuffer[depth];
		swapBuffer[depth] = board.arr[moves[i].starty][moves[i].startx];
		board.arr[moves[i].starty][moves[i].startx] = board.arr[moves[i].finaly][moves[i].finalx];
		board.arr[moves[i].finaly][moves[i].finalx] = swapBuffer[depth];
		// unswap

	}
	return result;

}

void bestChoice(Board &board, int searchDepth, char color, int turn) {
	int col = 0;
	if (color == 'b')
		col++;
	vector<Move> moveBuffer(searchDepth);
	vector<Piece*> swapBuffer(searchDepth);// this holds pieces that will be swapped into a buffer. Then we don't have to copy a bunch of boards
	for (int i = 0; i < searchDepth; i++)
		swapBuffer[i] = new Empty('E', -1, -1);
	boardSwapper(board,searchDepth, 0, swapBuffer,moveBuffer,col,0,turn,-1000000000,1000000000);
	// this will edit the board into the proper move
	// still need to delete swap buffer
	for (int i = 0; i < searchDepth; i++)
		delete swapBuffer[i];
	
	// make the move
	Piece* swappedPiece = new Empty('E', -1, -1);
	Piece* temp = swappedPiece;
	swappedPiece = board.arr[moveBuffer[0].finaly][moveBuffer[0].finalx];//captured piece
	board.arr[moveBuffer[0].finaly][moveBuffer[0].finalx] = temp;
	std::swap(board.arr[moveBuffer[0].finaly][moveBuffer[0].finalx], board.arr[moveBuffer[0].starty][moveBuffer[0].startx]);
	delete swappedPiece;
	// make the move

}

bool worthwhile(double immediatePos, double currentBest, char thisColor) {

	if (thisColor == 'b')
		return ((immediatePos * k) < currentBest);
	return ((immediatePos * k) > currentBest);


}
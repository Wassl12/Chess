#include "verification.h"
#include "position.h"
#include "swapping.h"
#include <iostream>
double k = 1;
int moveschecked = 0;
int movesCut = 0;

double boardSwapper(Board& board, int searchDepth, int depth, vector<Piece*>& swapBuffer, vector<Move>& moveBuffer, int turn, double alpha, double beta) {// this will swap
	// if color is odd, black
	// if color is even, white
	char col = 'b';
	if (turn % 2 == 0)
		col = 'w';
	if (depth == searchDepth) {
		/*for (auto mov : moveBuffer) {
			cout << mov.pieceType << "from " << int(mov.startx) << ' ' << int(mov.starty) << " to " << int(mov.finalx) << ' ' << int(mov.finaly) << '\n';
		}*/
		bool hang = false;
		double result = (board,turn,col, hang);
		if (!hang)
			return result;
		// otherwise it becomes unattainable to check for huge trades of material... and this can confound the position metric
		else if (turn % 2 == 1)
			return -1000000;
		return 10000000;
	}


	vector <Move> moves;
	moveMaker(board, moves, col);
	// now moves is full of different moves
	double threshold = 1000000000;
	if (turn % 2 == 0)// if white
		threshold *= -1;
	double result = 0;
	bool firstPass = true;
	for (unsigned int i = 0; i < moves.size(); i++) {
		if (beta <= alpha) {
			return result;
		}
		bool oldMoved = board.arr[moves[i].starty][moves[i].startx]->moved;
		
		if (moves[i].finalx < 0) {
			board.castle(moves[i].finalx, col);
		}
		else if ((moves[i].finaly == 0 || moves[i].finaly == 7) && moves[i].pieceType == 'P') {
			board.arr[moves[i].starty][moves[i].startx]->moved = true;
			Piece* temp = board.arr[moves[i].starty][moves[i].startx];
			board.arr[moves[i].starty][moves[i].startx] = swapBuffer[depth];
			swapBuffer[depth] = board.arr[moves[i].finaly][moves[i].finalx];
			board.arr[moves[i].finaly][moves[i].finalx] = new Queen(col,moves[i].finalx,moves[i].finaly);
			board.arr[moves[i].finaly][moves[i].finalx]->x = moves[i].finalx;
			board.arr[moves[i].finaly][moves[i].finalx]->y = moves[i].finaly;
			delete temp;
		}
		
		else {// SWAP
			board.arr[moves[i].starty][moves[i].startx]->moved = true;
			Piece* temp = board.arr[moves[i].starty][moves[i].startx];
			board.arr[moves[i].starty][moves[i].startx] = swapBuffer[depth];
			swapBuffer[depth] = board.arr[moves[i].finaly][moves[i].finalx];//captured piece
			board.arr[moves[i].finaly][moves[i].finalx] = temp;
			board.arr[moves[i].finaly][moves[i].finalx]->x = moves[i].finalx;
			board.arr[moves[i].finaly][moves[i].finalx]->y = moves[i].finaly;
			// SWAP
		}
		
			
		if (worthwhile(0, result,turn)) {
			moveschecked++;
			result = boardSwapper(board, searchDepth, depth + 1, swapBuffer, moveBuffer, turn+1,alpha,beta);
			//board.Print();
			firstPass = false;
		}
		else {
			movesCut++; // DIAGNOSTICS
		}
		if (turn % 2 == 1 && result < beta)// black edits the beta value
			beta = result; // For black
		if (turn % 2 == 0 && result > alpha)
			alpha = result; // For white
		if (turn % 2 == 1 && result <= threshold){// search for a minimum value
			moveBuffer[depth] = moves[i]; // black attempts to minimize value
			threshold = result;
			
		}
			
		else if (turn % 2 == 0 && result >= threshold) {
			moveBuffer[depth] = moves[i]; // white attempts to maximize
			threshold = result;
		}
			

		if (moves[i].finalx < 0)
			board.castle(moves[i].finalx, col);
		else if ((moves[i].finaly == 0 || moves[i].finaly == 7) && moves[i].pieceType == 'P') {
			
			Piece* empti = swapBuffer[depth];
			swapBuffer[depth] = board.arr[moves[i].starty][moves[i].startx];
			board.arr[moves[i].starty][moves[i].startx] = board.arr[moves[i].finaly][moves[i].finalx];
			board.arr[moves[i].finaly][moves[i].finalx] = empti;
			empti = board.arr[moves[i].starty][moves[i].startx];
			board.arr[moves[i].starty][moves[i].startx] = new Pawn(col, moves[i].startx, moves[i].starty);
			board.arr[moves[i].starty][moves[i].startx]->moved = oldMoved;
			delete empti;
		}
		else {// unswap
			
			Piece* empty = swapBuffer[depth];
			swapBuffer[depth] = board.arr[moves[i].starty][moves[i].startx];
			board.arr[moves[i].starty][moves[i].startx] = board.arr[moves[i].finaly][moves[i].finalx];
			board.arr[moves[i].finaly][moves[i].finalx] = empty;
			board.arr[moves[i].starty][moves[i].startx]->x = moves[i].startx;
			board.arr[moves[i].starty][moves[i].startx]->y = moves[i].starty;
			board.arr[moves[i].starty][moves[i].startx]->moved = oldMoved;
			// unswap
		}

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
	boardSwapper(board,searchDepth, 0, swapBuffer,moveBuffer,turn,-1000000000,1000000000);
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
	board.arr[moveBuffer[0].finaly][moveBuffer[0].finalx]->x = moveBuffer[0].finalx;
	board.arr[moveBuffer[0].finaly][moveBuffer[0].finalx]->y = moveBuffer[0].finaly;
	board.arr[moveBuffer[0].finaly][moveBuffer[0].finalx]->moved = true;
	delete swappedPiece;
	// make the move

}

bool worthwhile(double immediatePos, double currentBest, char thisColor) {
	return true;
	if (thisColor == 'b')
		return ((immediatePos * k) < currentBest);
	return ((immediatePos * k) > currentBest);


}
#include "verification.h"
#include "position.h"
#include "swapping.h"

double boardSwapper(Board& board, int searchDepth, int depth, vector<Piece*>& swapBuffer, vector<Move>& moveBuffer, long int color, double value) {// this will swap
	// if color is odd, black
	// if color is even, white

	if (depth == searchDepth) {
		return position(board);
	}
	vector <Move> moves;
	moveMaker(board, moves, color);
	// now moves is full of different moves
	double threshold = 1000000000;
	if (color % 2 == 0)
		threshold *= -1;
	double immediatePos = position(board);
	double result = 0;
	for (int i = 0; i < moves.size(); i++) {
		// two values at each point
		// immediate position -- can be calculated up front
		// leaf position -- this is the most optimal of all the leaf nodes

		Piece* temp = board.arr[moves[i].starty][moves[i].startx];
		board.arr[moves[i].starty][moves[i].startx] = swapBuffer[depth];
		swapBuffer[depth] = board.arr[moves[i].finaly][moves[i].finalx];//captured piece

		if (worthwhile(position(board), result)) {
			result = boardSwapper(board, searchDepth, depth + 1, swapBuffer, moveBuffer, color + 1, value);
		}


		if (color % 2 == 1 && result < threshold)// search for a minimum value
			threshold = result;
		else if (color % 2 == 0 && result > threshold)
			threshold = result;



		Piece* empty = swapBuffer[depth];
		swapBuffer[depth] = board.arr[moves[i].starty][moves[i].startx];
		board.arr[moves[i].starty][moves[i].startx] = board.arr[moves[i].finaly][moves[i].finalx];
		board.arr[moves[i].finaly][moves[i].finalx] = swapBuffer[depth];

	}


}

void bestChoice(int searchDepth) {

	vector<Move> moveBuffer(searchDepth);
	vector<Piece*> swapBuffer(searchDepth);// this holds pieces that will be swapped into a buffer. Then we don't have to copy a bunch of boards
	for (int i = 0; i < searchDepth; i++)
		swapBuffer[i] = new Empty('E', -1, -1);
	boardSwapper(searchDepth, 0, swapBuffer);
	// this will edit the board into the proper move

}

bool worthwhile(double immediatePos, double currentBest, char thisColor, double k) {

	if (thisColor == 'b')
		return ((immediatePos * k) < currentBest);
	return ((immediatePos * k) > currentBest);


}
// this is designed so the user doesn't make illegal moves(i.e. lets its king get captured)
#include "pieces.h"
#include <deque>
#include <algorithm>

struct Move {
	int8_t finaly;
	int8_t finalx;
	int8_t starty;
	int8_t startx;
	char pieceType;

};

void verify(Board &board, vector <Move>& moves) {
	// can swap pieces on the board with an empty piece to simulate a capture
	auto it = remove_if(moves.begin(), moves.end(), [&](Move &move) {return swapBoards(board, move); });
	moves.erase(it, moves.end());


}


bool swapBoards(Board& board, Move& mov) {
	char thisColor = board.arr[mov.startx][mov.starty]->color;

	Piece* swap = new Empty('E', -1, -1);


	Piece* temp = swap;
	swap = board.arr[mov.finaly][mov.finalx];//captured piece
	board.arr[mov.finaly][mov.finalx] = temp;
	std::swap(board.arr[mov.finaly][mov.finalx], board.arr[mov.starty][mov.startx]);
	// swap stores the destroyed piece

	bool result;
	if (thisColor == 'b')
		result = board.threatened(board.bKing->x, board.bKing->y, 'b');
	else
		result = board.threatened(board.wKing->x, board.wKing->y, 'w');

	std::swap(board.arr[mov.finaly][mov.finalx], board.arr[mov.starty][mov.startx]);
	std::swap(board.arr[mov.finaly][mov.finalx], temp);
	delete temp;
	return result;
}

void moveMaker(Board &board, vector <Move>& moves) {
	for (int y = 0; y < 8; y++) {
		for (int x = 0; x < 8; x++) {
			vector<pair<int8_t, int8_t>> positions;
			board.arr[y][x]->move(board, positions);

			for (auto pear : positions)
				moves.push_back({pear.first, pear.second,y,x, board.arr[y][x]->type});

		}
	}
	
}

void boardSwapper(int searchDepth, int depth, vector<Piece*> &swapBuffer) {// this will swap

	
	// FOR EACH SEARCH DEPTH, SWAP THE PIECES WITH PRIOR
	for (int depth = 0; depth < searchDepth; depth++) {





	}
}

void bestChoice(int searchDepth) {

	vector<Piece*> swapBuffer(searchDepth);// this holds pieces that will be swapped into a buffer. Then we don't have to copy a bunch of boards
	for (int i = 0; i < searchDepth; i++)
		swapBuffer[i] = new Empty('E', -1, -1);
	boardSwapper(searchDepth, 0, swapBuffer);
	// this will edit the board into the proper move

}
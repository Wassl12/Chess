// this is designed so the user doesn't make illegal moves(i.e. lets its king get captured)

#include <deque>
#include <algorithm>
#include "verification.h"
#include "pieces.h"
#include "position.h"



void verify(Board &board, vector <Move>& moves) {
	// can swap pieces on the board with an empty piece to simulate a capture
	auto it = remove_if(moves.begin(), moves.end(), [&](Move &move) {return swapBoards(board, move); });
	moves.erase(it, moves.end());


}


bool swapBoards(Board& board, Move& mov) {
	char thisColor = board.arr[mov.startx][mov.starty]->color;

	Piece* swappedPiece = new Empty('E', -1, -1);


	Piece* temp = swappedPiece;
	swappedPiece = board.arr[mov.finaly][mov.finalx];//captured piece
	board.arr[mov.finaly][mov.finalx] = temp;
	std::swap(board.arr[mov.finaly][mov.finalx], board.arr[mov.starty][mov.startx]);
	// swap stores the destroyed piece

	bool result;
	if (thisColor == 'b')
		result = board.threatened(board.bKing->x, board.bKing->y, 'b');
	else
		result = board.threatened(board.wKing->x, board.wKing->y, 'w');

	std::swap(board.arr[mov.finaly][mov.finalx], board.arr[mov.starty][mov.startx]);
	std::swap(board.arr[mov.finaly][mov.finalx], swappedPiece);
	delete temp;
	return result;
}

void moveMaker(Board &board, vector <Move>& moves, char color) {
	for (int8_t y = 0; y < 8; y++) {
		for (int8_t x = 0; x < 8; x++) {
			if (board.arr[y][x]->color == color) {
				vector<pair<int8_t, int8_t>> positions;
				board.arr[y][x]->move(board, positions);// positions gets filled

				for (auto pear : positions)// a pair of final y,x coordinates
					moves.push_back({ pear.first, pear.second,y,x, board.arr[y][x]->type });
			}
			

		}
	}
	
}

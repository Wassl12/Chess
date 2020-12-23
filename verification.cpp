// this is designed so the user doesn't make illegal moves(i.e. lets its king get captured)
#include "pieces.h"

struct Move {
	int8_t finaly;
	int8_t finalx;
	char pieceType;

};
void moveMaker(Board &board, vector <Move>& moves) {
	for (int y = 0; y < 8; y++) {
		for (int x = 0; x < 8; x++) {
			vector<pair<int8_t, int8_t>> positions;
			board.arr[y][x]->move(board, positions);

			for (auto pear : positions)
				moves.push_back({pear.first, pear.second, board.arr[y][x]->type});


		}
	}




}
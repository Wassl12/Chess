#include "position.h"
#include "pieces.h"
#include "swapping.h"
#include "verification.h"
#include "human.h"
#include <iostream>
#include <string>
#include <algorithm>

using namespace std;


int main() {

	cout << "Please enter preferred search depth: (8 is recommended, but 7 or 6 is also acceptable)" << endl;
	int searchDepth = 0;
	cin >> searchDepth;
	cout << "Would you like to play as white, black, or as a spectator?" << endl;
	string choice;
	cin >> choice;
	cout << "Please type moves as <Piece> <StartFile> <StartRank> <EndFile> <EndRank>" << endl;
	bool whiteUser = false;
	bool blackUser = false;
	
	if (choice[0] == 'w' || choice[0] == 'W')
		whiteUser = true;
	else if (choice[0] == 'b' || choice[0] == 'B')
		blackUser = true;
	Board board;
	int turn = 0;
	while (true) {
		cout << "turn #" << turn << '\n';
		board.Print();
		if (turn % 2 == 0) {// it's white's turn
			
			while (whiteUser) {
				Move movie = translate();
				if (!swapBoards(board, movie)) {// go through with the move
					Piece* swappedPiece = new Empty('E', -1, -1);
					Piece* temp = swappedPiece;
					swappedPiece = board.arr[movie.finaly][movie.finalx];//captured piece
					board.arr[movie.finaly][movie.finalx] = temp;
					std::swap(board.arr[movie.finaly][movie.finalx], board.arr[movie.starty][movie.startx]);
					delete swappedPiece;
					break;
				}
				else {
					cout << "Illegal move... try another one" << endl;
				}

			}
			if (!whiteUser)
				bestChoice(board, searchDepth,'w',turn);
		}
		else {

			while (blackUser) {
				Move movie = translate();
				if (!swapBoards(board, movie)) {// go through with the move
					Piece* swappedPiece = new Empty('E', -1, -1);
					Piece* temp = swappedPiece;
					swappedPiece = board.arr[movie.finaly][movie.finalx];//captured piece
					board.arr[movie.finaly][movie.finalx] = temp;
					std::swap(board.arr[movie.finaly][movie.finalx], board.arr[movie.starty][movie.startx]);
					delete swappedPiece;
					break;
				}
				else {
					cout << "Illegal move... try another one" << endl;
				}
			}
			if (!blackUser) {
				/*if (turn == 1) {
					std::swap(board.arr[1][3], board.arr[2][3]);
					board.arr[2][3]->moved = true;
				}
				else if (turn == 3) {
					std::swap(board.arr[1][4], board.arr[3][4]);
					board.arr[3][4]->moved = true;
				}
				else*/
					bestChoice(board, searchDepth, 'b', turn);
			}
				


		}

		turn++;
	}


}
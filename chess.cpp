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

	cout << "Please enter the search depth: (Somewhere between 2 and 5)" << endl;
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
		board.Print();
		if (turn % 2 == 0) {// it's white's turn
			
			while (whiteUser) {
				Move movie = translate(cin);
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
				bestChoice(board, searchDepth);
		}
		else {

			while (blackUser) {
				Move movie = translate(cin);
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
			if (!blackUser)
				bestChoice(board, searchDepth);


		}


	}


}
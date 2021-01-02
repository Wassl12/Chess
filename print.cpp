#pragma once
#include <iostream>
#include "pieces.h"

void Board::printChar(int row, int column) {
	this->arr[row][column]->Char();
}
void Board::Print() {
	// eleven underscores per grid
	for (int n = 0; n < 80; n++)
		std::cout << '_';
	cout << '\n';
	for (int i = 0; i < 8; i++) {
		
		for (int n = 0; n < 2; n++) {
			for (int i = 0; i <= 80; i++) {
				if (i % 10 == 0)
					std::cout << '|';
				else
					std::cout << ' ';
			}
			cout << '\n';
		}
		for (int r = 0; r <= 80; r++) {
			if (r % 10 == 4)
				printChar(i,r++/10);
			else if (r % 10 == 0)
				std::cout << '|';
			else
				std::cout << ' ';
			
		}
		cout << '\n';
		for (int n = 0; n < 1; n++) {
			for (int i = 0; i <= 80; i++) {
				if (i % 10 == 0)
					std::cout << '|';
				else
					std::cout << ' ';
			}
			cout << '\n';
		}
		for (int i = 0; i <= 80; i++) {
			if (i % 10 == 0)
				std::cout << '|';
			else
				std::cout << '_';
		}
		std::cout << '\n';
	}
	

}
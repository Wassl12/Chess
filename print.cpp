#pragma once
#include <iostream>
#include "pieces.h"

void Board::printChar(int row, int column) {
	this->arr[row][column]->Char();
}
void Board::Print() {
	// eleven underscores per grid
	
	for (int i = 0; i < 8; i++) {
		for(int n = 0; n < 88;n++)
			std::cout << '_';
		for (int n = 0; n < 5; n++) {
			for (int i = 0; i < 88; i++) {
				if (i % 11 == 0)
					std::cout << '|';
				else
					std::cout << ' ';
			}
		}
		for (int r = 0; r < 88; r++) {
			if (r % 11 == 5)
				printChar(i,r/11);
			else if (r % 11 == 0)
				std::cout << '|';
			else
				std::cout << ' ';
		}
		for (int n = 0; n < 5; n++) {
			for (int i = 0; i < 88; i++) {
				if (i % 11 == 0)
					std::cout << '|';
				else
					std::cout << ' ';
			}
		}

	}
	for (int i = 0; i < 88; i++) {
		std::cout << '_';
	}
	std::cout << '\n';

}
#pragma once
#include <stdint.h>
#include <vector>
using namespace std;
class Board {
public:
	std::vector <std::vector <Piece* > > arr;

	Board();
	void Print();
	void printChar(int row,int column);
	bool isLegal(int x, int y, char type);
};

class Piece {
public:
	char type;
	char color;
	int8_t x;
	int8_t y;
	virtual vector < pair<int8_t, int8_t> > move(Board& board) = 0;
	virtual void Char() = 0;
	Piece(char color, int8_t x, int8_t y);

};

class Pawn :  public Piece {
public:
	
	vector < pair<int8_t, int8_t> > move(Board& board);
	void Char();
	Pawn(char color, int8_t x, int8_t y);
};

class Rook : public Piece {
public:
	
	vector < pair<int8_t, int8_t> > move(Board& board);
	void Char();
	Rook(char color, int8_t x, int8_t y);
};

class Knight : public Piece {
public:
	
	vector < pair<int8_t, int8_t> >move(Board& board);
	void Char();
	Knight(char color, int8_t x, int8_t y);
};

class Bishop : public Piece {
public:
	
	vector < pair<int8_t, int8_t> > move(Board& board);
	void Char();
	Bishop(char color, int8_t x, int8_t y);
};

class Queen : public Piece {
public:
	
	vector < pair<int8_t, int8_t>> move(Board& board);
	void Char();
	Queen(char color, int8_t x, int8_t y);
};

class King : public Piece {
public:
	
	vector < pair<int8_t, int8_t> >move(Board& board);
	void Char();
	King(char color, int8_t x, int8_t y);
};

class Empty : public Piece {
public:
	
	Empty(char color, int8_t x, int8_t y);
	void Char();
	vector < pair<int8_t, int8_t>> move(Board& board);
};
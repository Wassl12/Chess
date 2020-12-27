#pragma once
#include <stdint.h>
#include <vector>
using namespace std;
class Board {
public:
	std::vector <std::vector <Piece* > > arr; // the physical board which contains pointers to pieces
	Piece* bKing;
	Piece* wKing;
	Board();
	void Print();
	void printChar(int row,int column);
	bool isLegal(int x, int y, char type);// helper function to avoid segmentation faults more making moves
	bool threatened(int x, int y, char defendingColor);//
	
	// no deconstructor 
};

class Piece {
public:
	char type;
	char color;
	bool moved;// if it has moved at all
	int8_t x;
	int8_t y;
	/*    x = 0		1		2		3		4		5		6		7
	y = 0     
	y = 1
	y = 2
	y = 3
	y = 4
	y = 5
	y = 6
	y = 7
	*/
	virtual void move(Board& board, vector < pair<int8_t, int8_t> > & moves) = 0;
	virtual void Char() = 0;// don't worry about it... just prints a char
	Piece(char color, int8_t x, int8_t y);

};

class Pawn :  public Piece {
public:
	
	void move(Board& board, vector < pair<int8_t, int8_t> >& moves);
	void Char();
	Pawn(char color, int8_t x, int8_t y);
};

class Rook : public Piece {
public:
	
	void move(Board& board, vector < pair<int8_t, int8_t> >& moves);
	void Char();
	Rook(char color, int8_t x, int8_t y);
};

class Knight : public Piece {
public:
	
	void move(Board& board, vector < pair<int8_t, int8_t> >& moves);
	void Char();
	Knight(char color, int8_t x, int8_t y);
};

class Bishop : public Piece {
public:
	
	void move(Board& board, vector < pair<int8_t, int8_t> >& moves);
	void Char();
	Bishop(char color, int8_t x, int8_t y);
};

class Queen : public Piece {
public:
	
	void move(Board& board, vector < pair<int8_t, int8_t> >& moves);
	void Char();
	Queen(char color, int8_t x, int8_t y);
};

class King : public Piece {
public:
	
	void move(Board& board, vector < pair<int8_t, int8_t> >& moves);
	void Char();
	King(char color, int8_t x, int8_t y);
};

class Empty : public Piece {
public:
	
	Empty(char color, int8_t x, int8_t y);
	void Char();
	void move(Board& board, vector < pair<int8_t, int8_t> >& moves);
};
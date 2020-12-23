#pragma once
#include <stdint.h>
#include <vector>
using namespace std;
class Board {
public:
	std::vector <std::vector <Piece* > > arr;
	Piece* bKing;
	Piece* wKing;
	Board();
	void Print();
	void printChar(int row,int column);
	bool isLegal(int x, int y, char type);
	bool threatened(int x, int y, char defendingColor);//
};

class Piece {
public:
	char type;
	char color;
	bool moved;// if it has moved at all
	int8_t x;
	int8_t y;
	virtual void move(Board& board, vector < pair<int8_t, int8_t> > & moves) = 0;
	virtual void Char() = 0;
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
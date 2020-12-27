#include "pieces.h"
#include <iostream>

Piece::Piece(char colorin, int8_t xin, int8_t yin) : color(colorin), x(xin), y(yin), moved(false) {}

Rook::Rook(char colorin, int8_t xin, int8_t yin) : Piece{ colorin,xin,yin } { type = 'R'; }

Knight::Knight(char colorin, int8_t xin, int8_t yin) :  Piece{ colorin, xin,yin } { type = 'N'; }

Bishop::Bishop(char colorin, int8_t xin, int8_t yin) : Piece{ colorin,xin,yin } { type = 'B'; }

Queen::Queen(char colorin, int8_t xin, int8_t yin) : Piece{ colorin,xin,yin } { type = 'Q'; }

King::King(char colorin, int8_t xin, int8_t yin) : Piece{ colorin,xin,yin} { type = 'K'; }

Pawn::Pawn(char colorin, int8_t xin, int8_t yin) : Piece{ colorin,xin,yin } { type = 'P'; }

Empty::Empty(char colorin, int8_t xin, int8_t yin) : Piece{ colorin,xin,yin } { type = 'E'; }

bool Board::isLegal( int y, int x, char color) {
	if (x < 0 || x > 7 || y < 0 || y > 7)// not a segfault
		return false;
	if (this->arr[y][x]->color == color)// if a similar piece is in the way
		return false;
	return true;

}
// print out piece name 
void Pawn::Char(){
	std::cout << 'P';
}

void King::Char() {
	std::cout << 'K';
}
void Queen::Char() {
	std::cout << 'Q';
}
void Bishop::Char() {
	std::cout << 'B';
}
void Knight::Char() {
	std::cout << 'N';
}
void Rook::Char() {
	std::cout << 'R';
}

void Empty::Char() {
	std::cout << 'E';
}


Board::Board() {
	
	arr[0][0] = new Rook('b',0, 0);
	arr[0][1] = new Knight('b',1, 0);
	arr[0][2] = new Bishop('b', 2, 0);
	arr[0][3] = new Queen('b', 3, 0);
	arr[0][4] = new King('b', 4, 0);
	bKing = arr[0][4];
	arr[0][5] = new Bishop('b', 5, 0);
	arr[0][6] = new Knight('b', 6, 0);
	arr[0][7] = new Rook('b', 7, 0);
	for (int i = 0; i < 8; i++) {
		arr[1][i] = new Pawn('b', i, 1);
	}
	for (int i = 0; i < 8; i++) {
		arr[6][i] = new Pawn('w', i, 6);
	}
	for (int row = 2; row < 6; row++) {
		for (int column = 0; column < 8; column++) {
			arr[row][column] = new Empty('e',0, 0);
		}
	}
	arr[7][0] = new Rook('w',7, 0);
	arr[7][1] = new Knight('w', 7, 1);
	arr[7][2] = new Bishop('w', 7, 2);
	arr[7][3] = new Queen('w', 7, 3);
	arr[7][4] = new King('w', 7, 4);
	wKing = arr[7][4];
	arr[7][5] = new Bishop('w', 7, 5);
	arr[7][6] = new Knight('w', 7, 6);
	arr[7][7] = new Rook('w', 7, 7);
}

// If the position function needs the other pieces, we can use a map/unordered map to store all valuable pointers
void Pawn::move(Board& board, vector <pair <int8_t, int8_t> > &moves) {
	// capture the thing in front

	//creates a bunch of pairs and fills a vector of pairs
	/*    x = 0		1		2		3		4		5		6		7
	y = 0
	y = 1	bp		bp		bp		bp
	y = 2
	y = 3
	y = 4
	y = 5
	y = 6
	y = 7
	*/
	if (this->color == 'b') {
		if (board.isLegal(this->y + 1, this->x, this->color))
			moves.push_back({ y + 1,x });
		if (board.isLegal(this->y+2,this->x,this->color) && !this->moved)
			moves.push_back({ y + 2,x });
		if (board.isLegal(this->y+1,this->x+1,'b'))
			moves.push_back({ y + 1,x+1 });
		if (board.isLegal(this->y + 1, this->x - 1, 'b'))
			moves.push_back({ y + 1,x - 1 });
	}
	else {
		if (board.isLegal(this->y-1,this->x,this->color))
			moves.push_back({ y - 1,x });
		if (board.isLegal(this->y-2,this->x,this->color) && !this->moved)
			moves.push_back({ y - 2,x });
		if (board.isLegal(this->y-1,this->x+1,this->color));
			moves.push_back({ y - 1,x + 1 });
		if (board.isLegal(this->y - 1, this->x - 1, this->color))
			moves.push_back({ y - 1,x - 1 });

	}
	
}

void Rook::move(Board& board, vector<pair<int8_t, int8_t> > & moves) {
	// set spoty and spotx to rook's current position
	int spoty = this->y;
	
	

	// checks moves to right 
	int spotx = this->x;
	spotx++;
	while (spotx < 8) {
		if (board.arr[this->y][spotx]->type == 'E')
			moves.push_back({ this->y,spotx });
		else if (board.arr[this->y][spotx]->color == this->color) // if it's same color
			break;
		else { 
			// if it's opposite color, takes the piece and breaks
			moves.push_back({ this->y,spotx });
			break;
		}
		spotx++;
	}
	

	// checks moves to left
	spotx = this->x;
	spotx--;
	while (spotx >= 0) {
		if (board.arr[this->y][spotx]->type == 'E')
			moves.push_back({ this->y,spotx });
		else if (board.arr[this->y][spotx]->color == this->color)// if it's same color
			break;
		else {
			// if it's opposite color, takes the piece and breaks
			moves.push_back({ this->y,spotx });
			break;
		}
		spotx--;
	}
	// checks left



	// check down
	spoty = this->y;
	spoty++;
	while (spoty < 8) {
		if (board.arr[spoty][this->x]->type == 'E')
			moves.push_back({ spoty,this->x });
		else if (board.arr[spoty][this->x]->color == this->color)
			break;
		else {
			// if it's opposite color, takes the piece and breaks
			moves.push_back({ spoty,this->x });
			break;
		}
		spoty++;
	}
	// check down



	// check up
	spoty = this->y;
	spoty--;
	while (spoty >= 0) {
		if (board.arr[spoty][this->x]->type == 'E')
			moves.push_back({ spoty,this->x });
		else if (board.arr[spoty][this->x]->color == this->color)
			break;
		else {
			moves.push_back({ spoty,this->x });
			break;
		}
		spoty--;
	}
	// check up
}

void Bishop::move(Board& board, vector <pair <int8_t, int8_t> > &moves) {
	//creates a bunch of pairs and fills a vector of pairs
	/*    x = 0		1		2		3		4		5		6		7
	y = 0
	y = 1	bp		bp		bp		bp
	y = 2
	y = 3
	y = 4
	y = 5
	y = 6
	y = 7
	*/


	// down right
	int spoty = this->y;
	int spotx = this->x;
	spoty++;
	spotx++;
	while (spotx < 8 && spoty < 8) {
		if (board.arr[spoty][spotx]->type == 'E')
			moves.push_back({ spoty,spotx });
		else if (board.arr[spoty][spotx]->color == this->color)
			break;
		else {
			moves.push_back({ spoty,spotx });
			break;
		}
		spotx++;
		spoty++;
	}
	// down right



	// up right
	int spoty = this->y;
	int spotx = this->x;
	spoty--;
	spotx++;
	while (spotx < 8 && spoty >= 0) {
		if (board.arr[spoty][spotx]->type == 'E')
			moves.push_back({ spoty,spotx });
		else if (board.arr[spoty][spotx]->color == this->color)
			break;
		else {
			moves.push_back({ spoty,spotx });
			break;
		}
		spotx++;
		spoty--;
	}
	// up right 

	// down left
	int spotx = this->x;
	int spoty = this->y;
	spotx--;
	spoty++;
	while (spotx >= 0 && spoty < 8) {
		if (board.arr[spoty][spotx]->type == 'E')
			moves.push_back({ spoty,spotx });
		else if (board.arr[spoty][spotx]->color == this->color)
			break;
		else {
			moves.push_back({ spoty,spotx });
			break;
		}
		spotx--;
		spoty++;
	}
	
	// down left

	// up left
	int spotx = this->x;
	int spoty = this->y;
	spotx--;
	spoty--;
	while (spotx >= 0 && spoty >= 0) {
		if (board.arr[spoty][spotx]->type == 'E')
			moves.push_back({ spoty,spotx });
		else if (board.arr[spoty][spotx]->color == this->color)
			break;
		else {
			moves.push_back({ spoty,spotx });
			break;
		}
		spotx--;
		spoty--;
	}
	// up left
}

void Queen::move(Board &board, vector <pair <int8_t, int8_t> > & moves) {
	
	// ROOK MOVES //////////////////////////

	int spoty = this->y;
	int spotx = this->x;
	spotx++;
	while (spotx < 8) {
		if (board.arr[this->y][spotx]->type == 'E')
			moves.push_back({ this->y,spotx });
		else if (board.arr[this->y][spotx]->color == this->color)
			break;
		else {
			moves.push_back({ this->y,spotx });
			break;
		}
		spotx++;
	}
	spotx = this->x;
	spotx--;
	while (spotx >= 0) {
		if (board.arr[this->y][spotx]->type == 'E')
			moves.push_back({ this->y,spotx });
		else if (board.arr[this->y][spotx]->color == this->color)
			break;
		else {
			moves.push_back({ this->y,spotx });
			break;
		}
		spotx--;
	}
	spoty++;
	while (spoty < 8) {
		if (board.arr[spoty][this->x]->type == 'E')
			moves.push_back({ spoty,this->x });
		else if (board.arr[spoty][this->x]->color == this->color)
			break;
		else {
			moves.push_back({ spoty,this->x });
			break;
		}
		spoty++;
	}
	spoty = this->y;
	spoty--;
	while (spoty >= 0) {
		if (board.arr[spoty][this->x]->type == 'E')
			moves.push_back({ spoty,this->x });
		else if (board.arr[spoty][this->x]->color == this->color)
			break;
		else {
			moves.push_back({ spoty,this->x });
			break;
		}
		spoty++;
	}
	////////// END ROOK ///////////

	////////// START BISHOP STYLE MOVES ///////////
	int spoty = this->y;
	int spotx = this->x;
	spoty++;
	spotx++;
	while (spotx < 8 && spoty < 8) {
		if (board.arr[spoty][spotx]->type == 'E')
			moves.push_back({ spoty,spotx });
		else if (board.arr[spoty][spotx]->color == this->color)
			break;
		else {
			moves.push_back({ spoty,spotx });
			break;
		}
		spotx++;
		spoty++;
	}
	int spoty = this->y;
	int spotx = this->x;
	spoty--;
	spotx++;
	while (spotx < 8 && spoty >= 0) {
		if (board.arr[spoty][spotx]->type == 'E')
			moves.push_back({ spoty,spotx });
		else if (board.arr[spoty][spotx]->color == this->color)
			break;
		else {
			moves.push_back({ spoty,spotx });
			break;
		}
		spotx++;
		spoty--;
	}
	int spotx = this->x;
	int spoty = this->y;
	spotx--;
	spoty++;
	while (spotx >= 0 && spoty < 8) {
		if (board.arr[spoty][spotx]->type == 'E')
			moves.push_back({ spoty,spotx });
		else if (board.arr[spoty][spotx]->color == this->color)
			break;
		else {
			moves.push_back({ spoty,spotx });
			break;
		}
		spotx--;
		spoty++;
	}
	int spotx = this->x;
	int spoty = this->y;
	spotx--;
	spoty--;
	while (spotx >= 0 && spoty >= 0) {
		if (board.arr[spoty][spotx]->type == 'E')
			moves.push_back({ spoty,spotx });
		else if (board.arr[spoty][spotx]->color == this->color)
			break;
		else {
			moves.push_back({ spoty,spotx });
			break;
		}
		spotx++;
		spoty--;
	}
	////////// END BISHOP STYLE MOVES ///////////
}

 void Knight::move(Board& board, vector <pair <int8_t, int8_t> > &moves) {
	// two up one right
	// two up one left
	// two right one up
	// two right one down
	// two down one left
	// two down one right
	// two left one up
	// two left one right
	
	if (board.isLegal(this->y + 2, this->x - 1, this->color))
		moves.push_back({ this->y + 2, this->x - 1 });
	if (board.isLegal(this->y + 2, this->x + 1, this->color))
		moves.push_back({ this->y + 2, this->x + 1 });

	if (board.isLegal(this->y + 1, this->x + 2, this->color))
		moves.push_back({ this->y + 1, this->x + 2 });
	if (board.isLegal(this->y - 1, this->x + 2, this->color))
		moves.push_back({ this->y - 1, this->x + 2 });

	if (board.isLegal(this->y - 2, this->x - 1, this->color))
		moves.push_back({ this->y - 2, this->x - 1 });
	if (board.isLegal(this->y - 2, this->x + 1, this->color))
		moves.push_back({ this->y - 2, this->x + 1 });

	if (board.isLegal(this->y + 1, this->x - 2, this->color))
		moves.push_back({ this->y + 1, this->x - 2 });
	if (board.isLegal(this->y - 1, this->x - 2, this->color))
		moves.push_back({ this->y - 1, this->x - 2 });

	

}

void King::move(Board &board, vector <pair <int8_t, int8_t > > &moves) {
	// THIS DOES NOT CHECK FOR ILLEGAL MOVES.
	//THIS WILL LATER BE VERIFIED TO PREVENT THE USER FROM DOING SOMETHING STUPID
	// up left
	// up right
	// down left
	// down right
	// left
	// right
	// up
	// down
	// Castle kingside
	// Castle queenside

	/*    x = 0		1		2		3		4		5		6		7
	y = 0
	y = 1	bp		bp		bp		bp
	y = 2
	y = 3
	y = 4
	y = 5
	y = 6
	y = 7
	*/

	// left
	if (board.isLegal(this->y, this->x - 1, this->color))
		moves.push_back({ this->y,this->x - 1 });
	// down left 
	if (board.isLegal(this->y+1, this->x - 1, this->color))
		moves.push_back({ this->y+1,this->x - 1 });
	// up left
	if (board.isLegal(this->y - 1, this->x - 1, this->color))
		moves.push_back({ this->y - 1,this->x - 1 });
	// up
	if (board.isLegal(this->y - 1, this->x, this->color))
		moves.push_back({ this->y - 1,this->x });
	// down
	if (board.isLegal(this->y + 1, this->x, this->color))
		moves.push_back({ this->y + 1,this->x });
	// right
	if (board.isLegal(this->y, this->x+1, this->color))
		moves.push_back({ this->y + 1,this->x+1 });
	// right up
	if (board.isLegal(this->y - 1, this->x + 1, this->color))
		moves.push_back({ this->y - 1,this->x + 1 });
	// right down
	if (board.isLegal(this->y + 1, this->x + 1, this->color))
		moves.push_back({ this->y + 1,this->x + 1 });
	// castle kingside
	if (!(this->moved || board.threatened(this->y, this->x, this->color) || board.threatened(this->y, this->x + 1, this->color) || board.threatened(this->y, this->x + 2, this->color) || board.arr[this->y][this->x + 3]->moved
		 || board.arr[this->y][this->x + 1]->type != 'E' || board.arr[this->y][this->x + 2]->type != 'E')) {
		moves.push_back({ -1,-1}); // special values
	}
	// castle queenside
	if (!(this->moved || board.threatened(this->y, this->x, this->color) || board.threatened(this->y, this->x - 1, this->color) || board.threatened(this->y, this->x - 2, this->color) 
		|| board.arr[this->y][this->x - 4]->moved
	    || board.arr[this->y][this->x - 1]->type != 'E' || board.arr[this->y][this->x - 2]->type != 'E' || board.arr[this->y][this->x-3]->type != 'E')) {
		moves.push_back({ -2,-2});// special values
	}

}

void Empty::move(Board& board, vector < pair<int8_t, int8_t> >& moves) {}
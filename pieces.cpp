#include "pieces.h"
#include <iostream>

Piece::Piece(char colorin, int8_t xin, int8_t yin, int valin) : color(colorin), x(xin), y(yin), value(valin), moved(false) {}

Rook::Rook(char colorin, int8_t xin, int8_t yin) : Piece{ colorin,xin,yin,5 } { type = 'R'; }

Knight::Knight(char colorin, int8_t xin, int8_t yin) :  Piece{ colorin, xin,yin,3 } { type = 'N'; }

Bishop::Bishop(char colorin, int8_t xin, int8_t yin) : Piece{ colorin,xin,yin,3 } { type = 'B'; }

Queen::Queen(char colorin, int8_t xin, int8_t yin) : Piece{ colorin,xin,yin,9 } { type = 'Q'; }

King::King(char colorin, int8_t xin, int8_t yin) : Piece{ colorin,xin,yin,UINT32_MAX/2} { type = 'K'; }

Pawn::Pawn(char colorin, int8_t xin, int8_t yin) : Piece{ colorin,xin,yin,1 } { type = 'P'; }

Empty::Empty(char colorin, int8_t xin, int8_t yin) : Piece{ colorin,xin,yin,0 } { type = 'E'; }

bool Board::isLegal( int y, int x, char color) {
	if (x < 0 || x > 7 || y < 0 || y > 7)// not a segfault
		return false;
	if (this->arr[y][x]->color == color)// if a similar piece is in the way
		return false;
	return true;

}
// print out piece name 
void Pawn::Char(){
	std::cout << this->color << 'P';
}

void King::Char() {
	std::cout << this->color << 'K';
}
void Queen::Char() {
	std::cout << this->color << 'Q';
}
void Bishop::Char() {
	std::cout << this->color << 'B';
}
void Knight::Char() {
	std::cout << this->color << 'N';
}
void Rook::Char() {
	std::cout << this->color << 'R';
}

void Empty::Char() {
	std::cout << "  ";
}


Board::Board() : arr(8,vector<Piece*>(8)) {
	
	arr[0][0] = new Rook('b',0, 0);
	blackPieceMap["Rook"].push_back(arr[0][0]);
	arr[0][1] = new Knight('b',1, 0);
	blackPieceMap["Knight"].push_back(arr[0][1]);
	arr[0][2] = new Bishop('b', 2, 0);
	blackPieceMap["Bishop"].push_back(arr[0][2]);
	arr[0][3] = new Queen('b', 3, 0);
	blackPieceMap["Queen"].push_back(arr[0][3]);
	arr[0][4] = new King('b', 4, 0);
	blackPieceMap["King"].push_back(arr[0][4]);
	bKing = arr[0][4];
	arr[0][5] = new Bishop('b', 5, 0);
	blackPieceMap["Bishop"].push_back(arr[0][5]);
	arr[0][6] = new Knight('b', 6, 0);
	blackPieceMap["Knight"].push_back(arr[0][6]);
	arr[0][7] = new Rook('b', 7, 0);
	blackPieceMap["Rook"].push_back(arr[0][7]);
	for (int i = 0; i < 8; i++) {
		arr[1][i] = new Pawn('b', i, 1);
		blackPieceMap["Pawn"].push_back(arr[1][i]);
	}
	for (int i = 0; i < 8; i++) {
		arr[6][i] = new Pawn('w', i, 6);
		whitePieceMap["Pawn"].push_back(arr[6][i]);
	}
	for (int row = 2; row < 6; row++) {
		for (int column = 0; column < 8; column++) {
			arr[row][column] = new Empty('e',0, 0);
		}
	}
	arr[7][0] = new Rook('w',7, 0);
	whitePieceMap["Rook"].push_back(arr[7][0]);
	arr[7][1] = new Knight('w', 7, 1);
	whitePieceMap["Knight"].push_back(arr[7][1]);
	arr[7][2] = new Bishop('w', 7, 2);
	whitePieceMap["Bishop"].push_back(arr[7][2]);
	arr[7][3] = new Queen('w', 7, 3);
	whitePieceMap["Queen"].push_back(arr[7][3]);
	arr[7][4] = new King('w', 7, 4);
	whitePieceMap["King"].push_back(arr[7][4]);
	wKing = arr[7][4];
	arr[7][5] = new Bishop('w', 7, 5);
	whitePieceMap["Bishop"].push_back(arr[7][5]);
	arr[7][6] = new Knight('w', 7, 6);
	whitePieceMap["Knight"].push_back(arr[7][6]);
	arr[7][7] = new Rook('w', 7, 7);
	whitePieceMap["Rook"].push_back(arr[7][7]);
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
		if (board.isLegal(this->y+1,this->x+1,'b') && board.arr[y+1][x+1]->type != 'E')
			moves.push_back({ y + 1,x+1 });
		if (board.isLegal(this->y + 1, this->x - 1, 'b') && board.arr[y + 1][x - 1]->type != 'E')
			moves.push_back({ y + 1,x - 1 });
	}
	else {
		if (board.isLegal(this->y-1,this->x,this->color))
			moves.push_back({ y - 1,x });
		if (board.isLegal(this->y-2,this->x,this->color) && !this->moved)
			moves.push_back({ y - 2,x });
		if (board.isLegal(this->y-1,this->x+1,this->color) && board.arr[y - 1][x + 1]->type != 'E')
			moves.push_back({ y - 1,x + 1 });
		if (board.isLegal(this->y - 1, this->x - 1, this->color) && board.arr[y - 1][x - 1]->type != 'E')
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
	 spoty = this->y;
	 spotx = this->x;
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
	 spotx = this->x;
	 spoty = this->y;
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
	 spotx = this->x;
	 spoty = this->y;
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
	 spoty = this->y;
	 spotx = this->x;
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
	 spoty = this->y;
	 spotx = this->x;
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
	 spotx = this->x;
	 spoty = this->y;
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
	 spotx = this->x;
	 spoty = this->y;
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

/*        x = 0		1		2		3		4		5		6		7
	y = 0     
	y = 1
	y = 2
	y = 3
	y = 4
	y = 5
	y = 6
	y = 7
	*/
	
/*bool Board::threatened(int x, int y, char defendingColor){

	// FINISHED but crawling with beetlejuices :(
	
	// loop to checks all possible knights
	for(int i = 0; i < 8; ++i){
		
		// checks knights up and to left/right
		if(i < 2){
			int copy_y = y - 2;
			if (i == 0) {
				// checks up left
				int copy_x = x + -1;
				if (0 <= copy_x && copy_x <= 7 && 0 <= copy_y &&  copy_y <= 7) {
					if(this->arr[copy_y][copy_x]->type == 'K' && this->arr[copy_y][copy_x]->color != defendingColor){
						return true;
					}
				}
				}
			else{
				// checks up right
				int copy_x = x +1;
				if (0 <= copy_x && copy_x <= 7 && 0 <= copy_y &&  copy_y <= 7) {
					if(this->arr[copy_y][copy_x]->type == 'K' && this->arr[copy_y][copy_x]->color != defendingColor){
						return true;
					}
				}
			}
		}
		// checks knights right and up left/down right
		else if(i < 4){
			int copy_x = x + 2;
			if (i == 2) {
				// checks right then up left
				
				int copy_y = y -1;
				if (0 <= copy_x && copy_x <= 7 && 0 <= copy_y &&  copy_y <= 7) {
					if(this->arr[copy_y][copy_x]->type == 'K' && this->arr[copy_y][copy_x]->color != defendingColor){
						return true;
					}
				}
				}
			else{
				// checks 
				int copy_y = y +1 ;
				if (0 <= copy_x && copy_x <= 7 && 0 <= copy_y &&  copy_y <= 7) {
					if(this->arr[copy_y][copy_x]->type == 'K' && this->arr[copy_y][copy_x]->color != defendingColor){
						return true;
					}
				}
			}
		}
		// checks knights down and then left/right
		else if(i <6){
			int copy_y = y + 2;
			if (i == 4) {
				// checks down left
				int copy_x = x - 1;
				
				if (0 <= copy_x && copy_x <= 7 && 0 <= copy_y &&  copy_y <= 7) {
					if(this->arr[copy_y][copy_x]->type == 'K' && this->arr[copy_y][copy_x]->color != defendingColor){
						return true;
					}
				}
				


				}
			else{
				// checks down right
				int copy_x = x +1;
				if (0 <= copy_x && copy_x <= 7 && 0 <= copy_y &&  copy_y <= 7) {
					if(this->arr[copy_y][copy_x]->type == 'K' && this->arr[copy_y][copy_x]->color != defendingColor){
						return true;
					}
				}
			}
		}
		// checks knights left and then up left/right
		else{
			int copy_x = x - 2;
			if (i == 6) {
				// checks left then up
				
				int copy_y = y -1;
				if (0 <= copy_x && copy_x <= 7 && 0 <= copy_y &&  copy_y <= 7) {
					if(this->arr[copy_y][copy_x]->type == 'K' && this->arr[copy_y][copy_x]->color != defendingColor){
						return true;
					}
				}
				


				}
			else{
				// checks left then down
				int copy_y = y +1 ;
				if (0 <= copy_x && copy_x <= 7 && 0 <= copy_y &&  copy_y <= 7) {
					if(this->arr[copy_y][copy_x]->type == 'K' && this->arr[copy_y][copy_x]->color != defendingColor){
						return true;
					}
				}
			}	

		}
	}

	// checks for bounds so it can limit the search of pieces and make sure there are no indexes out of bounds. 

	int copy_x = x;
	int copy_y = y;

	// checks horizontal to the left for threats

	while(copy_x >= 0){
		
		if(this->arr[y][x]->color == defendingColor){
			break;
		}
		
		else if(this->arr[y][x]->color != defendingColor && (this->arr[y][x]->color == 'Q' || this->arr[y][x]->color == 'R')){
			return true;
		}
		
		--copy_x;
	}
	copy_x = x;

	while(copy_x <= 7){
		
		if(this->arr[y][x]->color == defendingColor){
			break;
		}
		
		else if(this->arr[y][x]->color != defendingColor && (this->arr[y][x]->color == 'Q' || this->arr[y][x]->color == 'R')){
			return true;
		}
		
		++copy_x;
	}

	// checks horizontal towards 7 for threats

	copy_x = x;
	while(copy_y <= 7){
		
		if(this->arr[y][x]->color == defendingColor){
			break;
		}
		
		else if(this->arr[y][x]->color != defendingColor && (this->arr[y][x]->color == 'Q' || this->arr[y][x]->color == 'R')){
			return true;
		}
		
		++copy_y;
	}
	copy_y = y;

	// checks horizontal towards 0 for threats

	while(0 <= copy_y ){
		
		if(this->arr[y][x]->color == defendingColor){
			break;
		}
		
		else if(this->arr[y][x]->color != defendingColor && (this->arr[y][x]->color == 'Q' || this->arr[y][x]->color == 'R')){
			return true;
		}
		
		--copy_y;
	}
	copy_y = y;

	// checks upper left diagonal towards x=0,y=0 for a threat

	while(0 <= copy_x && 0 <= copy_y ){

		// another pawn check for defending white upper left square.
		if(copy_x == (x-1) && copy_y == (y-1)){
			if (defendingColor == 'w') {
				if( this->arr[copy_y][copy_x]->type == 'P' && this->arr[copy_y][copy_x]->color == 'B'){ 
					return true;
				}
			}
		}
		if(this->arr[y][x]->color == defendingColor){
			break;
		}
		
		else if(this->arr[y][x]->color != defendingColor && (this->arr[y][x]->color == 'Q' || this->arr[y][x]->color == 'B')){
			return true;
		}
		
		--copy_y;
		--copy_x;
	}
	copy_y = y;
	copy_x = x;

	// checks upper right diagonal towards x=7,y=0 horizontal for a threat

	while( 7 >= copy_x && 0 <= copy_y ){
		// this checks for pawns, only for when the defending color is white.
		if(copy_x == (x+1) && copy_y == (y-1)){
			if (defendingColor == 'w') {
				if( this->arr[copy_y][copy_x]->type == 'P' && this->arr[copy_y][copy_x]->color == 'B'){ 
					return true;
				}
			}
		}

		if(this->arr[y][x]->color == defendingColor){
			break;
		}
		
		else if(this->arr[y][x]->color != defendingColor && (this->arr[y][x]->color == 'Q' || this->arr[y][x]->color == 'B')){
			return true;
		}
		
		--copy_y;
		++copy_x;
	}
	copy_y = y;
	copy_x = x;

	// checks bottom left diagonal towards x=0,y=7 horizontal for a threat

	while( 0 <= copy_x &&  7 >= copy_y ){

		if(copy_x == (x-1) && copy_y == (y+1)){
			if (defendingColor == 'b') {
				if( this->arr[copy_y][copy_x]->type == 'P' && this->arr[copy_y][copy_x]->color == 'w'){ 
					return true;
				}
			}
		}
			
		
		if(this->arr[y][x]->color == defendingColor){
			break;
		}
		
		else if(this->arr[y][x]->color != defendingColor && (this->arr[y][x]->color == 'Q' || this->arr[y][x]->color == 'B')){
			return true;
		}
		
		++copy_y;
		--copy_x;
	}
	copy_y = y;
	copy_x = x;

	// checks bottom right horizontal towards x=7, y=7 for a threat

	while( 7 >= copy_x && 7 >= copy_y ){
		
		if(copy_x == (x+1) && copy_y == (y-1)){
			if (defendingColor == 'b') {
				if( this->arr[copy_y][copy_x]->type == 'P' && this->arr[copy_y][copy_x]->color == 'w'){ 
					return true;
				}
			}
		}

		if(this->arr[y][x]->color == defendingColor){
			break;
		}
		
		else if(this->arr[y][x]->color != defendingColor && (this->arr[y][x]->color == 'Q' || this->arr[y][x]->color == 'B')){
			return true;
		}
		
		--copy_y;
		++copy_x;
	}
	return false;
	
}*/

bool Board::threatened(int x, int y, char defendingColor) {
	// 8 while loops
	// 8 knight checks
	int8_t xLook = x;
	int8_t yLook = y;
	// LEFT WHILE LOOP
	while (xLook >= 0) {
		if (arr[y][xLook]->type == 'E')// most likely
			continue;
		else if (arr[y][xLook]->color == defendingColor || (arr[y][xLook]->type != 'R' && arr[y][xLook]->type != 'Q') && (arr[y][xLook]->type != 'K' || x - xLook > 1))// something in the way, break
			break;
		else
			return true;

		xLook--;
	}
	xLook = x;
	// RIGHT WHILE LOOP
	while (xLook <= 7) {
		if (arr[y][xLook]->type == 'E')
			continue;
		else if (arr[y][xLook]->color == defendingColor || (arr[y][xLook]->type != 'R' && arr[y][xLook]->type != 'Q' && (arr[y][xLook]->type != 'K' || xLook - x > 1)))
			break;
		else
			return true;

		xLook++;
	}
	xLook = x;
	// UP WHILE LOOP
	while (yLook >= 0) {
		if (arr[yLook][x]->type == 'E')
			continue;
		else if (arr[yLook][x]->color == defendingColor || (arr[yLook][x]->type != 'R' && arr[yLook][x]->type != 'Q' && (arr[yLook][x]->type != 'K' || y - yLook > 1)))
			break;
		else
			return true;

		yLook--;
	}
	yLook = y;
	// DOWN WHILE LOOP
	while (yLook <= 7) {
		if (arr[yLook][x]->type == 'E')
			continue;
		else if (arr[yLook][x]->color == defendingColor || (arr[yLook][x]->type != 'R' && arr[yLook][x]->type != 'Q' && (arr[yLook][x]->type != 'K' || yLook - y > 1)))
			break;
		else
			return true;

		yLook++;
	}
	yLook = y;
	xLook = x;
	// DOWN RIGHT WHILE LOOP
	while (yLook <= 7 && xLook <= 7) {
		if (arr[yLook][xLook]->type == 'E')
			continue;
		else if (arr[yLook][xLook]->color == defendingColor || (arr[yLook][xLook]->type != 'B' && arr[yLook][xLook]->type != 'Q' && (arr[yLook][xLook]->type != 'K' || yLook - y > 1 || xLook - x > 1)))
			break;
		else
			return true;
		yLook++;
		xLook++;
	}
	yLook = y;
	xLook = x;
	// DOWN LEFT WHILE LOOP
	while (yLook <= 7 && xLook >= 0) {
		if (arr[yLook][xLook]->type == 'E')
			continue;
		else if (arr[yLook][xLook]->color == defendingColor || (arr[yLook][xLook]->type != 'B' && arr[yLook][xLook]->type != 'Q' && (arr[yLook][xLook]->type != 'K' || yLook - y > 1 || x - xLook > 1)))
			break;
		else
			return true;
		yLook++;
		xLook--;
	}
	yLook = y;
	xLook = x;
	// UP RIGHT WHILE LOOP
	while (yLook >= 0 && xLook <= 7) {
		if (arr[yLook][xLook]->type == 'E')
			continue;
		else if (arr[yLook][xLook]->color == defendingColor || (arr[yLook][xLook]->type != 'B' && arr[yLook][xLook]->type != 'Q' && (arr[yLook][xLook]->type != 'K' || y - yLook > 1 || xLook - x > 1)))
			break;
		else
			return true;
		yLook--;
		xLook++;
	}
	yLook = y;
	xLook = x;
	// UP LEFT WHILE LOOP
	while (yLook >= 0 && xLook >= 0) {
		if (arr[yLook][xLook]->type == 'E')
			continue;
		else if (arr[yLook][xLook]->color == defendingColor || (arr[yLook][xLook]->type != 'B' && arr[yLook][xLook]->type != 'Q' && (arr[yLook][xLook]->type != 'K' || y - yLook > 1 || x - xLook > 1)))
			break;
		else
			return true;
		yLook--;
		xLook--;
	}

	// 8 Knight checks
	if (y < 6 && x < 7 && arr[y + 2][x + 1]->type == 'N' && arr[y + 2][x + 1]->color != defendingColor)
		return true;
	if (y < 7 && x < 6 && arr[y + 1][x + 2]->type == 'N' && arr[y + 1][x + 2]->color != defendingColor)
		return true;

	if (y > 1 && x < 7 && arr[y - 2][x + 1]->type == 'N' && arr[y - 2][x + 1]->color != defendingColor)
		return true;
	if (y > 0 && x < 6 && arr[y - 1][x + 2]->type == 'N' && arr[y - 1][x + 2]->color != defendingColor)
		return true;

	if (y > 1 && x > 0 && arr[y - 2][x - 1]->type == 'N' && arr[y - 2][x - 1]->color != defendingColor)
		return true;
	if (y > 0 && x > 1 && arr[y - 1][x - 2]->type == 'N' && arr[y - 1][x - 2]->color != defendingColor)
		return true;

	if (y < 6 && x > 0 && arr[y + 2][x - 1]->type == 'N' && arr[y + 2][x - 1]->color != defendingColor)
		return true;
	if(y < 7 && x > 1 && arr[y + 1][x - 2]->type == 'N' && arr[y + 1][x - 2]->color != defendingColor)
		return true;
	
	// PASSED ALL CHECKS
	return false;

}

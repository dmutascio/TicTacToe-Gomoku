#include "Gomoku.h"
#include "Header.h"
#include <iomanip>

using namespace std;

//construct GomokuGame object with correct dimensions and fills the board with empty space
GomokuGame::GomokuGame() : GameBase(static_cast<int>(gameConstruct::dimGokomu), static_cast<int>(gameConstruct::dimGokomu), static_cast<int>(gameConstruct::longest), true, static_cast<int>(gameConstruct::startMoves), static_cast<int>(gameConstruct::dimGokomuPrint), static_cast<int>(gameConstruct::dimGokomuPrint)), bMoves("Black: "), wMoves("White: ") {
	for (size_t c = 0; c < (width+1) * (height+1); ++c) {
		board.push_back(" ");
	}
}

// created operater to print board. Prints row label and then the respective row, continually with a for loop. Then prints column labels with seperate loop
ostream& operator<<(ostream& stream, const GomokuGame& game) {
	for (size_t y = game.height; y > 0; --y) {
		cout << setw(game.longest) << y;
		for (size_t x = 1; x <= game.width; ++x) {
			cout << setw(game.longest) << game.board[y * game.width + x];
		}
		cout << endl;
	}
	cout << setw(game.longest) << "X";
	for (size_t c = 1; c <= game.width; ++c) {
		cout <<  setw(game.longest) << c;
	}
	cout << endl;
	return stream;
}

//prints the game using defined insertion operator
void GomokuGame::print() {
	cout << *this;
}

//checks if the boards done by checking 4 possible winning scenarios
bool GomokuGame::done() {
	//vertical
	//iterates through every column. Assumes true (win). If it finds a column is not a win (ie no 5 in a row), jumps out of  nested for loop and skips over returning true
	//iteratest through next column, until we reached the end. 
	for (size_t x = 1; x <= width; ++x) {
		for (size_t y = 1; y <= height - 4; ++y) {
			for (size_t p = y; p < y + 4; ++p) {
				if (board[(p) * width + x] != board[(p + 1) * width + x] || (board[p * width + x] == " ")) {
					goto FALSEVERT;
				}
			}
			return true;
			FALSEVERT:
			continue;
		}
	}

	//horizontal
	//iterates through every row. Assumes true (win). If it finds a column is not a win (ie no 5 in a row), jumps out of  nested for loop and skips over returning true
	//iteratest through next column, until we reached the end. 
	for (size_t y = 1; y <= height; ++y) {
		for (size_t x = 1; x <= height - 4; ++x) {
			for (size_t p = x; p < x + 4; ++p) {
				if (board[y * width + p] != board[y * width + (p + 1)] || (board[y * width + p] == " ")) {
					goto FALSEHORIZ;
				}
			}
			return true;
			FALSEHORIZ:
			continue;
		}
	}

	//diag bottomLeft-topRight...upper
	for (size_t i = 1; i <= static_cast<int>(gameConstruct::dimGokomu) - 4; ++i) {
		for (size_t j = 0; j <= (height - 4) - i; ++j) {
			int y = i + j;
			int x = j + 1;
			for (size_t p = 0; p < 4; p++) {
				if (board[(y + p) * width + (x + p)] != board[(y + p + 1) * width + (x + p + 1)] || (board[y * width + x] == " ")) {
					goto FALSEDIAG1;
				}
			}
			return true;
			FALSEDIAG1:
			continue;
		}
	}

	//diag bottomLeft-topRight...lower
	for (size_t i = 1; i < static_cast<int>(gameConstruct::dimGokomu) - 4; ++i) {
		for (size_t j = 1; j <= (height - 4) - i; ++j) {
			int y = j;
			int x = i+j;
			for (size_t p = 0; p < 4; p++) {
				if (board[(y + p) * width + (x + p)] != board[(y + p + 1) * width + (x + p + 1)] || (board[y * width + x] == " ")) {
					goto FALSEDIAG2;
				}
			}
			return true;
			FALSEDIAG2:
			continue;
		}
	}

	//diag bottomright-topLeft...upper
	for (size_t i = 1; i <= static_cast<int>(gameConstruct::dimGokomu) - 4; ++i) {
		for (size_t j = 0; j <= (height-4)-i; ++j) {
			int y = i + j;
			int x = width-j;
			for (size_t p = 0; p < 4; p++) {
				if (board[(y + p) * width + (x - p)] != board[(y + p + 1) * width + (x - p - 1)] || (board[y * width + x] == " ")) {
					goto FALSEDIAG3;
				}
			}
			return true;
			FALSEDIAG3:
			continue;
		}
	}
	
	//diag bottomright-topLeft...lower
	for (size_t i = 0; i < static_cast<int>(gameConstruct::dimGokomu) - 5; ++i) {
		for (size_t j = 1; j < (height - 4) - i; ++j) {
			int y = j;
			int x = width - (i+j);
			for (size_t p = 0; p < 4; p++) {
				if (board[(y + p) * width + (x - p)] != board[(y + p + 1) * width + (x - p - 1)] || (board[y * width + x] == " ")) {
					goto FALSEDIAG4;
				}
			}
			return true;
			FALSEDIAG4:
			continue;
		}
	}

	return false;
}


//fill boared with blakc/white and use done() function to see if either piece can still win
bool GomokuGame::draw() {
	GomokuGame copy = *this;
	for (size_t x = 1; x <= width; ++x) {
		for (size_t y = 1; y <= height; ++y) {
			if (board[y * width + x] == " ") {
				copy.board[y * width + x] = "B";
			}
		}
	}
	
	if (copy.done() == true) {
		return false;
	}

	for (size_t x = 1; x <= width; ++x) {
		for (size_t y = 1; y <= height; ++y) {
			if (board[y * width + x] == " ") {
				copy.board[y * width + x] = "W";
			}
		}
	}
	if (copy.done() == true) {
		return false;
	}

	return true;
}

//prompts user to input coordinates using previous method. if the space is empty and program could succesfully read coordinates, updates board and record of moves for respective player
//prints board using operater method and adjusts whos turn it is
int GomokuGame::turn() {
	string player;
	if (xTurn) {
		player = "B";
		cout << endl << "Player Black" << endl;
	}
	else {
		player = "W";
		cout << endl << "Player White" << endl;
	}

	unsigned int x, y;
	while (true) {
		int input = prompt(x, y);
		if (input == static_cast<int>(errorMessage::userQuit)) {
			return static_cast<int>(errorMessage::userQuit);
		}
		if (board[y * width + x] == " " && input == static_cast<int>(errorMessage::success)) {
			board[y * width + x] = player;
			string move = " " + to_string(x) + "," + to_string(y);
			if (xTurn) {
				bMoves += move;
			}
			else {
				wMoves += move;
			}
			break;
		}

	}

	cout << endl << *this << endl;
	if (xTurn) {
		cout << bMoves << endl;
	}
	else {
		cout << wMoves << endl;
	}

	xTurn = !xTurn;
	numMoves++;
	return static_cast<int>(errorMessage::turnSuccess);
}
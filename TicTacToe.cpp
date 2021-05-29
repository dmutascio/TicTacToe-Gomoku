#include "TicTacToe.h"
#include "Header.h"
#include <iomanip>

using namespace std;

//construct TicTacToeGame object with correct dimensions and fills the board with empty space
TicTacToeGame::TicTacToeGame() : GameBase(static_cast<int>(gameConstruct::dimTTT), static_cast<int>(gameConstruct::dimTTT), static_cast<int>(gameConstruct::longest), true, static_cast<int>(gameConstruct::startMoves), static_cast<int>(gameConstruct::dimTTT), static_cast<int>(gameConstruct::dimTTT)), xMoves("X: "), oMoves("O: ") {
	for (size_t c = 0; c < width * height; ++c) {
		board.push_back(" ");
	}
}

// created operater to print board. Prints row label and then the respective row, continually with a for loop. Then prints column labels with seperate loop
ostream& operator<<(ostream& stream, const TicTacToeGame& game) {
	for (size_t y = game.height; y > 0; --y) {
		cout << y - 1;
		for (size_t x = 0; x < game.width; ++x) {
			cout << setw(game.longest) << game.board[(y - 1) * game.width + x];
		}
		cout << endl;
	}
	cout << " ";
	for (size_t c = 0; c < game.width; ++c) {
		cout << setw(game.longest) << c;
	}
	cout << endl;
	return stream;
}

//checks if the boards done by checking 4 possible winning scenarios
bool TicTacToeGame::done() {
	//vertical
	//iterates through every column. Assumes true (win). If it finds a column is not a win (ie its not all the same piece), jumps out of  nested for loop and skips over returning true
	//iteratest through next column, until we reached the end. 
	for (size_t x = 1; x < width - 1; ++x) {
		for (size_t y = 1; y < height - 2; ++y) {
			if (board[y * width + x] != board[(y + 1) * width + x] || (board[y * width + x] == " ")) {
				goto FALSEVERT;
			}
		}
		return true;
	FALSEVERT:
		continue;
	}



	//horizontal
	//iterates through every row. Assumes true (win). If it finds a row is not a win (ie its not all the same piece), jumps out of  nested for loop and skips over returning true
	//iteratest through next row, until we reached the end. 
	for (size_t y = 1; y < height - 1; ++y) {
		for (size_t x = 1; x < width - 2; ++x) {
			if (board[y * width + x] != board[y * width + (x + 1)] || (board[y * width + x] == " ")) {
				goto FALSEHORIZ;
			}
		}
		return true;
	FALSEHORIZ:
		continue;
	}

	//diagonal bottomL -> topR
	//assumes diagnoal is a win. iterates through the diagonal and if a different piece is found, stop iterating and jump over returning true
	for (size_t i = 1; i < width - 2; ++i) {
		if (board[i * width + i] != board[(i + 1) * width + (i + 1)] || (board[i * width + i] == " ")) {
			goto FALSEDIAG1;
		}
	}
	return true;
FALSEDIAG1:

	//diagonal bottomR -> topR
	//assumes diagnoal is a win. Iterates through the diagonal and if a different piece is found, stop iterating and jump over returning true
	for (size_t i = width - 2; i > 1; --i) {
		if (board[((height - 1) - i) * width + i] != board[(((height - 1) - i) + 1) * width + (i - 1)] || board[((height - 1) - i) * width + i] == " ") {
			goto FALSEDIAG2;
		}
	}
	return true;
FALSEDIAG2:

	return false;
}

//iterates through board to see if there are any empty spaces. If not, game is a draw
bool TicTacToeGame::draw() {
	if (done() != true) {
		for (size_t y = height - 2; y > 0; --y) {
			for (size_t x = 1; x < width - 1; ++x) {
				if (board[y * width + x] == " ") {
					return false;
				}
			}
		}
	}
	return true;
}

//prompts user to input coordinates using previous method. if the space is empty and program could succesfully read coordinates, updates board and record of moves for respective player
//prints board using operater method and adjusts whos turn it is
int TicTacToeGame::turn() {
	string player;
	if (xTurn) {
		player = "X";
		cout << endl << "Player 1" << endl;
	}
	else {
		player = "O";
		cout << endl << "Player 2" << endl;
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
				xMoves += move;
			}
			else {
				oMoves += move;
			}
			break;
		}

	}

	cout << endl << *this << endl;
	if (xTurn) {
		cout << xMoves << endl;
	}
	else {
		cout << oMoves << endl;
	}

	xTurn = !xTurn;
	numMoves++;
	return static_cast<int>(errorMessage::turnSuccess);
}

//prints the game using defined insertion operator
void TicTacToeGame::print() {
	cout << *this;
}
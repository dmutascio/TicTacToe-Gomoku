#include "GameBase.h"
#include "Header.h"
#include "TicTacToe.h"
#include "Gomoku.h"

using namespace std;

//GameBase constructor. Initializes member variables as what's passed in
GameBase::GameBase(int width, int height, int longest, bool xTurn, int numMoves, int widthBoard, int heightBoard) : width(width), height(height), longest(longest), xTurn(xTurn), numMoves(numMoves), widthBoard(widthBoard), heightBoard(heightBoard) {
}

//prompts user to input coordinates. checks if user wants to quit. if not, reads the input into x and y variables if formatted correctly. if not, prints out error statement and calls itself to restart process
int GameBase::prompt(unsigned int& int1, unsigned int& int2) {
	string input;
	cout << endl << "Please enter coordinates as two comma-seperated numbers (ex: 1,1) or 'quit' if you would like to quit: ";
	getline(cin, input);

	if (lower(input) == "quit") {
		return static_cast<int>(errorMessage::userQuit);
	}

	int found = input.find(',');
	if (found != string::npos) {
		input[found] = ' ';
	}

	istringstream iss(input);
	if (iss >> int1 >> int2) {
		if (int1 < widthBoard - 1 && int1 > 0) {
			if (int2 < heightBoard - 1 && int2 > 0) {
				return static_cast<int>(errorMessage::success);
			}
		}
	}
	cout << endl << "Error. Please enter the coordinates as two comma seperated numbers (ex: 1,1)" << endl;
	return prompt(int1, int2);
}

//prints board to start off. continually calls previous methods to play the game. print out respective ending messages
int GameBase::play() {
	print();
	cout << endl;
	while (true) {
		if (turn() == static_cast<int>(errorMessage::userQuit)) {
			cout << endl << "Game has ended. Number of moves: " << numMoves << endl;
			return static_cast<int>(errorMessage::userQuit);
		}
		else if (done()) {
			if (!xTurn) {
				cout << endl << "Player 1 won" << endl;
			}
			else {
				cout << endl << "Player 2 won" << endl;
			}
			return static_cast<int>(errorMessage::success);
		}
		else if (draw()) {
			cout << endl << "Game is a draw. Number of moves: " << numMoves << endl;
			return static_cast<int>(errorMessage::gameDraw);
		}
	}
}

//method used in main. checks if # command args is correct. if so, if the name passed in is either of the games, creates and returns the game
//otherwise return nullptr
shared_ptr<GameBase> GameBase::game(int argc, char* argv[]) {
	if (argc == static_cast<int>(indices::numArgs)) {
		if (static_cast<string>(argv[static_cast<int>(indices::gameName)]) == "TicTacToe") {
			shared_ptr<GameBase> game = make_shared<TicTacToeGame>();
			return game;
		}
		if (static_cast<string>(argv[static_cast<int>(indices::gameName)]) == "Gomoku") {
			shared_ptr<GameBase> game = make_shared<GomokuGame>();
			return game;
		}
	}
	return nullptr;
}

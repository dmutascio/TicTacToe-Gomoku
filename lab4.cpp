// lab4.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "Header.h"
#include "GameBase.h"
#include "TicTacToe.h"
#include "Gomoku.h"

using namespace std;

int main(int argc, char* argv[])
{
	//uses game() from base class to create correct game
	//calls usage method if incorrect read
	shared_ptr<GameBase> game = GameBase::game(argc, argv);
	if (game == nullptr) {
		return static_cast<int>(usageMessage(argv[static_cast<int>(indices::programName)]));
	}

	//runs the respective game function
	return game->play();
}

errorMessage usageMessage(char* progName) {
    //prints usage message with correct program name. returns fail key since it's only called when something cant execute
    cout << "usage " << progName << " TicTacToe/Gomoku" << endl;
    return errorMessage::wrongNumArgs;
}

string lower(string& upperString) {

	//string that will hold all the characters in lowercase
	string lower;

	//goes through each character and, if it's upper case, add its respective lower case. If not, it adds the same character in upperString65
	for (size_t s = 0; s < upperString.size(); s++) {
		if (static_cast<int>(lowerHelper::upperLow) <= upperString[s] && upperString[s] <= static_cast<int>(lowerHelper::upperHigh)) {
			lower += upperString[s] + static_cast<int>(lowerHelper::changeCase);
		}
		else {
			lower += upperString[s];
		}
	}
	return lower;
}


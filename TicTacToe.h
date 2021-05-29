#pragma once
#include <string>
#include <iostream>
#include <vector>
#include "GameBase.h"

//defining TicTacToeClass
class TicTacToeGame : public GameBase {
	friend std::ostream& operator<<(std::ostream&, const TicTacToeGame&);
private:
	std::string xMoves;
	std::string oMoves;
public:
	TicTacToeGame();
	virtual bool done() override;
	virtual bool draw() override;
	virtual int turn() override;
	virtual void print() override;
};

std::ostream& operator<<(std::ostream& stream, const TicTacToeGame& game);
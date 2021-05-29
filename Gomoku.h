#pragma once
#include "GameBase.h"

//defining Gomoku class
class GomokuGame : public GameBase {
	friend std::ostream& operator<<(std::ostream&, const GomokuGame&);
private:
	std::string bMoves;
	std::string wMoves;
public:
	GomokuGame();
	virtual bool done() override;
	virtual bool draw() override;
	virtual int turn() override;
	virtual void print() override;
};

std::ostream& operator<<(std::ostream& stream, const GomokuGame& game);
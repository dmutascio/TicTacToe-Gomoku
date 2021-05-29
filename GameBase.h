#pragma once
#include <string>
#include <vector>
#include <memory>

//defining GameBase class
class GameBase {
protected:
	GameBase(int width, int height, int longest, bool xTurn, int numMoves, int widthBoard, int heightBoard);
	unsigned int width;
	unsigned int height;
	unsigned int widthBoard;
	unsigned int heightBoard;
	unsigned int longest;
	bool xTurn;
	int numMoves;
	std::vector<std::string> board;
	virtual void print() = 0;
	virtual bool done() = 0;
	virtual bool draw() = 0;
	virtual int turn() = 0;
	virtual int prompt(unsigned int&, unsigned int&);
public:
	int play();
	static std::shared_ptr<GameBase> game(int argc, char* argv[]);
};
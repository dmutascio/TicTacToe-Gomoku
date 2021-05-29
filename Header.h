#pragma once
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>

//enumerations used throughout program
enum struct indices { programName = 0, gameName, commandLineArg, numArgs=2 };
enum struct errorMessage { success = 0, failToOpen, wrongNumArgs, wrongDim, noRead, userQuit, turnSuccess, gameDraw };
enum struct gameConstruct { dimTTT = 5, startMoves = 0, longest = 3, dimGokomu = 19, dimGokomuPrint=21 };
enum struct lowerHelper { upperLow = 65, upperHigh = 90, changeCase = 32 };

//declare the functions being using in main source file
errorMessage usageMessage(char*); 
std::string lower(std::string&);
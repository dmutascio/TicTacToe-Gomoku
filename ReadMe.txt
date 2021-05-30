Lab 4
David Mutascio 473129

Trials:
1) vs code threw an error showing vector subspace overflow
		-Problem was how I made my boards. TicTacToe board is from 0-4, while the Gomoku board starts at 1. Because of this, Gomoku board wasnt constructed to the correct size. 
		-Changed for loop to account for the different dimension scales

2) numMoves was 1 more than it should be and the wrong player was starting
		-I accidentally flipped positions in the constructors for each game. xTurn was being initialized to numMoves and numMoves to xTurn
		-flipped them

3) draw() kept returning true
		-logic behind the function was flipped. i was returning true is the copied board filled with one piece was true, which means the game is not a draw
		-flipped true/false

Tests:
		Tested all winning scenarios many times. Tested improper coordinate input and inputs that already exist. Tested out of bounds coordinates. Tested 'quit'.
		Tested improper command line argument. Tested different game name commands. Program was functional in all these tests

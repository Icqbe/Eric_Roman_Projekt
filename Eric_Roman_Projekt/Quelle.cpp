#include "Board.h"
#include <iostream>;
using namespace std;

void main() {

	Board connect4;
	int row;
	connect4.createBoard();
	//connect4.printBoardConsole();


	while (true) {
		connect4.printBoardConsole();
		cin >> row;
		connect4.playMove(row);

		if (connect4.checkWin(row)) {
			connect4.printBoardConsole();
			cout << "Player " << char(connect4.player) << " has won!\n";
			break;
		}
	}
	
	return;
}
#include "Board.h"
#include <iostream>
//#include <assert.h>
//#include <typeinfo>

using namespace std;

void main() {

	Board connect4;
	int row;
	connect4.createBoard();
	//connect4.printBoardConsole();


	while (true) {
		connect4.printBoardConsole();
		cin >> row;
		//assert(typeid(row) == typeid(int));
		if (row==99) {
			connect4.saveBoard();
			return;
		}
		connect4.playMove(row);

		if (connect4.checkWin(row)) {
			connect4.printBoardConsole();
			cout << "Player " << char(connect4.player) << " has won!\n";
			break;
		}
	}
	
	return;
}
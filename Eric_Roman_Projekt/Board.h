#pragma once
//Spielbrett 7 Spalten 6 Reihen, 21 Spielsteine je Spieler, Abwechselnd, Vier in einer Reihe gewinnt (diagonal, senkrecht, waagrecht)
class Board
{
public:
	//int column;
	//int row;
	int counterPlayer1=21;
	int counterPlayer2=21;
	void createBoard();
	int board[7][6];
	void printBoardConsole();
	bool playMove(int row);
	bool moveAvailable(int row);
	bool checkWin(int row);
	int lastAvailable;
	int player;

};


#include "Board.h"
#include <iostream>
#include <string>
#include <libpq-fe.h>
using namespace std;

//Spielbrett 7 Spalten 6 Reihen, 21 Spielsteine je Spieler, Abwechselnd, Vier in einer Reihe gewinnt (diagonal, senkrecht, waagrecht)

void Board::createBoard() {
	for (int i = 1; i <= 7; i++) {
		for (int j = 1; j <= 6; j++) {
			board[i - 1][j - 1] = '-';
		}
	}

	return;
}

void Board::saveBoard() {
	PGconn* connection;
	connection = PQconnectdb("host=localhost port=5432 dbname=postgres user=postgres password=0");
	if (PQstatus(connection) != CONNECTION_BAD) {
		cout << "Connection okay\n";
	}
	else {
		cout << "Connection bad\n";
	}

	//PQexec(connection, "select * from board");
	string insertStatement = "INSERT INTO board(countplayer1, countplayer2, board, lastavailable, player) VALUES(";
	insertStatement+= to_string(counterPlayer1);
	insertStatement += ", ";
	insertStatement += to_string(counterPlayer2);
	insertStatement += ", '{";
	for (int i=0; i < 6; i++) {

		insertStatement += "{";
		for (int j=0; j < 7; j++) {
			if (j == 6) {
				insertStatement += to_string(board[j][i]);
				break;
			}
			insertStatement += to_string(board[j][i]);
			insertStatement += ", ";

		}
		if (i == 5) {
			insertStatement += "} ";
			break;
		}
		insertStatement += "}, ";
	}

	insertStatement += "}', ";
	insertStatement += to_string(lastAvailable);
	insertStatement += ", ";
	insertStatement += to_string(player);
	insertStatement += ");";
	cout<< insertStatement;
	
	PGresult* res = PQexec(connection, insertStatement.c_str());
	
	ExecStatusType est = PQresultStatus(res);
	if (est != PGRES_COMMAND_OK) {
		cout << "Query unsuccessful";
	}
	else {
		cout << "Query successful";
	}
	
}

void Board::printBoardConsole() {
	cout << "Board:\n";
	for (int i = 1; i <= 6; i++) {
		for (int j = 1; j <= 7; j++) {
			cout << (char)board[j - 1][i - 1] << " ";
		}
		cout << "\n";
	}

}

bool Board::moveAvailable(int row) {
	if (board[row][0] != '-') {
		cout << "row " << row << " is full!\n";
		return false;
	}
	return true;
}

bool Board::playMove(int row) {
	if (!moveAvailable(row)) {
		return false;
	}

	for (int i = 1; i <= 6; i++) {
		if (board[row][i - 1] != '-') {
			break;
		}
		lastAvailable = i - 1;
	}

	if (counterPlayer1 >= counterPlayer2) {
		board[row][lastAvailable] = 'x';
		counterPlayer1 -= 1;
	}
	else if (counterPlayer2 > 0) {
		board[row][lastAvailable] = 'o';
		counterPlayer2 -= 1;
	}
	else {
		cout << "No more moves available!\n";
		return false;
	}
	return true;
}
bool checkCounter(int &counter) {
	if (counter >= 4){
	return true;
	}
	counter = 1;
	return false;
}
// board[row][lastAvailable]
bool Board::checkWin(int row) {
	int counter = 1;
	player = board[row][lastAvailable];
	int x = row;
	int y = lastAvailable;

	//Down
	do {
		counter += 1;
		y++;
	} while (x<7 && y<6 && board[x][y] == player);
	counter -= 1;
	y = lastAvailable;

	//Up
	do {
		counter += 1;
		y--;
	} while (x < 7 && y >= 0 && board[x][y] == player);
	counter -= 1;
	y = lastAvailable;

	if (checkCounter(counter)) {
		return true;
	}

	//Left
	do {
		counter += 1;
		x--;
	} while (x >=0 && y < 6 && board[x][y] == player);
	counter -= 1;
	x = row;

	//Right
	do {
		counter += 1;
		x++;
	} while (x < 7 && y < 6 && board[x][y] == player);
	counter -= 1;
	x = row;

	if (checkCounter(counter)) {
		return true;
	}

	//Up Left
	do {
		counter += 1;
		x--;
		y--;
	} while (x>=0 && y >= 0 && board[x][y] == player);
	counter--;
	x = row;
	y = lastAvailable;

	//Bottom Right
	do {
		counter += 1;
		x++;
		y++;
	} while (x < 7 && y < 6 && board[x][y] == player);
	counter--;
	x = row;
	y = lastAvailable;

	if (checkCounter(counter)) {
		return true;
	}

	//Down Left
	do {
		counter += 1;
		x--;
		y++;
	} while (x >=0 && y < 6 && board[x][y] == player);
	counter--;
	x = row;
	y = lastAvailable;

	//Up right
	do {
		counter += 1;
		x++;
		y--;
	} while (x < 7 && y >= 0 && board[x][y] == player);
	counter--;
	x = row;
	y = lastAvailable;

	if (checkCounter(counter)) {
		return true;
	}

	return false;
}

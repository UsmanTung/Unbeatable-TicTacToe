#include <iostream>
#include <string>
#include <stdlib.h>
#include <algorithm>
using namespace std;

/**This program is a Tic Tac Toe game
@author: Usman Tung
*/

void DisplayBoard(char** arr);
void ResetBoard(char** board);
void PlayerMove(char** board, int move);
char HaveWinner(char** arr);
int Menu();
void EasyComputerMove(char** arr);
int Evaluate(char** arr);
void HardComputerMove(char** arr);
int BestMove(char** arr);
bool isEmpty(char** arr, int i, int j);
int MiniMax(char** arr, int depth, bool isMax);

void main() {
	int move = 0;
	char** board = new char* [3];
	char piece = '1';
	for (int i = 0; i < 3; i++) {
		board[i] = new char[3];
		for (int j = 0; j < 3; j++) {
			board[i][j] = piece++;
		}
	}

	int option = 0;
	do {
		if (option == 1) {
			DisplayBoard(board);
			char hw = NULL;
			while (hw == NULL) {
				PlayerMove(board, move);
				DisplayBoard(board);
				hw = HaveWinner(board);
				move++;
				if (hw != NULL) {
					if (hw == 'D') {
						cout << "It's a draw!" << endl;
					}
					else {
						cout << "Player " << hw << " won!" << endl;
					}
					ResetBoard(board);
					move = 0;
				}
			}
		}
		if (option == 2) {
			DisplayBoard(board);
			char hw = NULL;
			while (hw == NULL) {
				if (move % 2 == 0) {
					PlayerMove(board, move);
					DisplayBoard(board);
				}
				else {
					EasyComputerMove(board);
					DisplayBoard(board);
				}
				hw = HaveWinner(board);
				move++;
				if (hw != NULL) {
					if (hw == 'D') {
						cout << "It's a draw!" << endl;
					}
					else {
						cout << "Player " << hw << " won!" << endl;
					}
					ResetBoard(board);
					move = 0;
				}
			}
		}
		if (option == 3) {
			DisplayBoard(board);
			char hw = NULL;
			while (hw == NULL) {
				if (move % 2 == 0) {
					PlayerMove(board, move);
					DisplayBoard(board);
				}
				else {
					HardComputerMove(board);
					DisplayBoard(board);
				}
				hw = HaveWinner(board);
				move++;
				if (hw != NULL) {
					if (hw == 'D') {
						cout << "It's a draw!" << endl;
					}
					else {
						cout << "Player " << hw << " won!" << endl;
					}
					ResetBoard(board);
					move = 0;
				}
			}

		}
		option = Menu();
	} while (option != 0);
	delete[] board;
	board = nullptr;

	exit(0);



}

int Menu() {
	int choice = NULL;
	cout << "0: Exit Tic Tac Toe" << endl;
	cout << "1: Player Vs Player" << endl;
	cout << "2: Player vs Easy Computer" << endl;
	cout << "3: Player vs Hard Computer" << endl;
	cin >> choice;
	while (choice < 0 || choice > 3) {
		cout << "Error Invalid Input. Please try again." << endl;
		cout << endl;
		cout << "0: Exit Tic Tac Toe" << endl;
		cout << "1: Player Vs Player" << endl;
		cout << "2: Player vs Easy Computer" << endl;
		cout << "3: Player vs Hard Computer" << endl;
		cin >> choice;
	}
	return choice;
}

void HardComputerMove(char** arr) {
	int place = BestMove(arr);
	arr[(place - 1) / 3][(place - 1) % 3] = 'O';
}


void EasyComputerMove(char** arr) {
	bool spaceEmpty = false;
	do {
		int col = rand() % 3;
		int row = rand() % 3;
		if (arr[row][col] == 'X' || arr[row][col] == 'O') {
			spaceEmpty = false;
		}
		else {
			spaceEmpty = true;
			arr[row][col] = 'O';
		}
	} while (!spaceEmpty);
}

int Evaluate(char** arr) {
	char result = HaveWinner(arr);
	if (result == 'O') {
		return 100;
	}
	if (result == 'X') {
		return -100;
	}
	return 0;
}

int BestMove(char** arr) {
	int bestMove = -1;
	int bestVal = -10000;
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			if (isEmpty(arr, i, j)) {
				arr[i][j] = 'O';
				int moveVal = MiniMax(arr, 0, false);
				arr[i][j] = '0'+ (i * 3 + j + 1);

				if (moveVal > bestVal) {
					bestVal = moveVal;
					bestMove = i * 3 + j + 1;
				}
			}
		}
	}
	return bestMove;
}
bool isEmpty(char** arr, int i, int j) {
	bool empty = false;
	if (arr[i][j] == 'X' || arr[i][j] == 'O') {
		return false;
	}
	return true;
}
int MiniMax(char** arr, int depth, bool isMax) {
	int evaluation = Evaluate(arr);
	if (evaluation == 100) {
		return evaluation;
	}
	if (evaluation == -100) {
		return evaluation;
	}
	if (HaveWinner(arr) == 'D') {
		return 0;
	}
	if (isMax) {
		int best = -10000;
		for (int i = 0; i < 3; i++) {
			for (int j = 0; j < 3; j++) {
				if (isEmpty(arr, i, j)) {
					arr[i][j] = 'O';
					best = max(best, MiniMax(arr, depth + 1, !isMax));
					arr[i][j] = '0'+(i * 3 + j + 1);

				}
			}
		}
		return best;
	}
	else {
		int best = 10000;
		for (int i = 0; i < 3; i++) {
			for (int j = 0; j < 3; j++){
				if (isEmpty(arr, i, j)) {
					arr[i][j] = 'X';
					best = min(best, MiniMax(arr, depth + 1,!isMax));
					arr[i][j] = '0'+(i*3+j + 1);
				}
}
		}
		return best;
	}
}
char HaveWinner(char** arr) {
	for (int i = 0; i < 3; i++) {
		if (arr[i][0] == 'X' && arr[i][1] == 'X' && arr[i][2] == 'X') {
			return 'X';
		}
		if (arr[0][i] == 'X' && arr[1][i] == 'X' && arr[2][i] == 'X') {
			return 'X';
		}
		if (arr[0][i] == 'O' && arr[1][i] == 'O' && arr[2][i] == 'O') {
			return 'O';
		}
		if (arr[i][0] == 'O' && arr[i][1] == 'O' && arr[i][2]=='O') {
			return 'O';
		}
	}
	if (arr[0][0] == 'X' && arr[1][1] == 'X' && arr[2][2] == 'X') {
		return 'X';
	}
	if (arr[0][2] == 'X' && arr[1][1] == 'X' && arr[2][0] == 'X') {
		return 'X';
	}
	if (arr[0][0] == 'O' && arr[1][1] == 'O' && arr[2][2] == 'O') {
		return 'O';
	}
	if (arr[0][2] == 'O' && arr[1][1] == 'O' && arr[2][0] == 'O') {
		return 'O';
	}
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			if (!(arr[i][j] == 'O' || arr[i][j] == 'X')) {
				return NULL;
			}
		}
		
	}
	return 'D';
}

void PlayerMove(char** arr, int move) {
	int place;
	char player = 'O';
	if (move % 2 == 0) {
		player = 'X';
	}
	cout << "Player "<<player<<", choose a number to place your piece: ";
	cin >> place;

	bool numInRange = false;
	bool spaceEmpty = false;
	do {
		if (place < 1 || place > 9) {
			numInRange = false;
		}
		else {
			numInRange = true;
		}

		if (numInRange) {
			char xo = arr[(place - 1) / 3][(place - 1) % 3];
			if (xo == 'X' || xo == 'O') {
				spaceEmpty = false;
			}
			else {
				spaceEmpty = true;
			}
		}

		if (numInRange && spaceEmpty) {
			arr[(place - 1) / 3][(place - 1) % 3] = player;
		}
		else {
			numInRange = false;
			spaceEmpty = false;
			cout << "Error! Invalid input." << endl;
			cout << "Player " << player << ", choose a number to place your piece: ";
			cin >> place;
		}
	} while (!numInRange && !spaceEmpty);
}

void DisplayBoard(char** arr) {

	cout << "   Tic Tac Toe   " << endl;
	cout << endl;
	cout << "     |     |     "<<endl;
	cout << "  "<<arr[0][0]<<"  |  "<<arr[0][1]<<"  |  "<<arr[0][2]<<"  " << endl;
	cout << "_____|_____|_____" << endl;
	cout << "     |     |     " << endl;
	cout << "  " << arr[1][0] << "  |  " << arr[1][1] << "  |  " << arr[1][2] << "  " << endl;
	cout << "_____|_____|_____" << endl;
	cout << "     |     |     " << endl;
	cout << "  " << arr[2][0] << "  |  " << arr[2][1] << "  |  " << arr[2][2] << "  " << endl;
	cout << "     |     |     " << endl;
}

void ResetBoard(char** board) {
	char piece = '1';
	for (int i = 0; i < 3; i++) {
		board[i] = new char[3];
		for (int j = 0; j < 3; j++) {
			board[i][j] = piece++;
		}
	}

}
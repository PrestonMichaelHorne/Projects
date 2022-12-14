#include "Party.h"
#include <cstdlib>
#include <iostream>

Board::Board(int size2) {
	size = size2;
	board = new char*[size];
	for (int i = 0; i < size; i++) {
		board[i] = new char[size];
		for (int j = 0; j < size; j++) {
			if (i == 0 || i == size - 1) {
				board[i][j] = '-';
				continue;
			}
			else if (j == 0 || j == size - 1) {
				board[i][j] = '|';
				continue;
			}
			board[i][j] = ' ';
		}
	}

	p = new Party();

	numM = rand() % 6 + 5;
	numT = rand() % 6 + 5;
}

Board::~Board() {
	cout << "Deleting Board..\n";
	for (int i = 0; i < size; i++) {
		delete [] board[i];
	}
	delete [] board;

	cout << "Deleting Treasure..\n";
	for (int i = 0; i < numT; i++) {
		delete [] t[i];
	}
	delete [] t;

	delete m;
	
	delete p;
}

ostream& operator<<(ostream& o, const Board& b) {
	for (int i = 0; i < b.size; i++) {
		for (int j = 0; j < b.size; j++) {
			o << b.board[i][j] << "\t";
		}
		o << "\n\n";
	}
return o;
}

void Board::setupEntrance() {
	int wall = rand() % 4;
	int pos = rand() % (size - 2) + 1;
	switch (wall) {
	case 0:
		board[pos][0] = 'X';
		(*p).SetRow(pos);
		(*p).SetCol(0);
		board[pos - 1][0] = '-';
		board[pos + 1][0] = '-';
		break;

	case 1:
		board[0][pos] = 'X';
		(*p).SetRow(0);
		(*p).SetCol(pos);
		board[0][pos - 1] = '|';
		board[0][pos + 1] = '|';
		break;

	case 2:
		board[pos][size - 1] = 'X';
		(*p).SetRow(pos);
		(*p).SetCol(size - 1);
		board[pos - 1][size - 1] = '-';
		board[pos + 1][size - 1] = '-';
		break;

	case 3:
		board[size - 1][pos] = 'X';
		(*p).SetRow(size - 1);
		(*p).SetCol(pos);
		board[size - 1][pos - 1] = '|';
		board[size - 1][pos + 1] = '|';
		break;
	}
}

void Board::setupMonsters() {
	for (int i = 0; i < numM; i++) {
		int x = (rand() % (size - 2) + 1);
		int y = (rand() % (size - 2) + 1);
		board[x][y] = 'M';
	}
}

void Board::setupTreasure() {
	t = new int* [numT];
	for (int i = 0; i < numT; i++) {
		int r = (rand() % (size - 2) + 1);
		int c = (rand() % (size - 2) + 1);
		board[r][c] = 'T';
		t[i] = new int[2];
		t[i][0] = r;
		t[i][1] = c;
	}
}

void Board::MoveParty() {
	char action;
	cout << "Enter N, S, E, or W to Move the Party: ";
	cin >> action;
	board[(*p).GetRow()][(*p).GetCol()] = ' ';
	switch (action) {
	case 'N':
		(*p).SetRow((*p).GetRow() - 1);
		break;

	case 'S':
		(*p).SetRow((*p).GetRow() + 1);
		break;

	case 'E':
		(*p).SetCol((*p).GetCol() + 1);
		break;

	case 'W':
		(*p).SetCol((*p).GetCol() - 1);
		break;
	}
	
	for (int i = 0; i < numT; i++) {
		if (t[i][0] == (*p).GetRow() && t[i][1] == (*p).GetCol()) {
			(*p).SetReward((rand() % 10) + 1);
			(*p).SetTreasure((*p).GetTreasure() + 1);
		}
	}

	if (board[(*p).GetRow()][(*p).GetCol()] == 'M') {
		bool running = false;
		char letter;
		m = new MonsterParty;
		cout << "Would the party like to run away? (y or n): ";
		cin >> letter;
		if (letter == 'y') {
			if (((*m).GetNumMonsters() == 5 && ((rand() % 100) + 1) <= 10)
				|| ((*m).GetNumMonsters() == 4 && ((rand() % 100) + 1) <= 20)
				|| ((*m).GetNumMonsters() == 3 && ((rand() % 100) + 1) <= 30)
				|| ((*m).GetNumMonsters() == 2 && ((rand() % 100) + 1) <= 40)
				|| ((*m).GetNumMonsters() == 1 && ((rand() % 100) + 1) <= 50))
			{
				running = true;
				delete m;
				cout << "Successfully ran from monsters\n";
				bool placed = false;
				while (!placed) {
					int x = rand() % (size - 2) + 1;
					int y = rand() % (size - 2) + 1;

					if (board[x][y] == ' ') {
						board[x][y] = 'M';
						placed = true;
					}
				}
			}
		}

		if (!running) {
			if (letter == 'y') {
				cout << "Running away failed by chance\n";
			}
			Combat();
		}
		
	}

	board[(*p).GetRow()][(*p).GetCol()] = 'X';

}

void Board::Display() {
	cout << (*p);
}

void Board::CheckStatus() {
	(*p).CheckStatus();
}

void Board::Combat() {

	bool monstersDead = false;
	bool playersDead = false;

	do {
		int target1 = 0;
		int target2 = 0;
		int target3 = 0;
		int target4 = 0;
		int target5 = 0;

		cout << (*m) << "\n\n";
		if ((*p).GetIsAlive(1)) {
			cout << "Character 1, Enter Your Target Monster: ";

			cin >> target1;
				if (((rand() % 100) + 1) > 15) {
					(*m).SetHealth(target1, (*p).GetPower(1));
					cout << "Character 1 attacked Monster " << target1 << "\n";
					cout << "Status of Monster " << target1 << " - \n";
					if ((*m).GetHealth(target1) <= 0) {
						(*m).Death(target1);
						cout << "Monster" << target1 << " is dead.\n";
					}
					(*m).PrintMonster(target1);
					cout << "\n\n";
				}
				else {
					cout << "Attack Missed Due to Chance\n";
				}
		}
		if ((*p).GetIsAlive(2)) {

			cout << "Character 2, Enter Your Target Monster: \n";

			cin >> target2;
				if (((rand() % 100) + 1) > 15) {
					(*m).SetHealth(target2, (*p).GetPower(2));
					cout << "Character 2 attacked Monster " << target2 << "\n";
					cout << "Status of Monster " << target2 << " - \n";
					if ((*m).GetHealth(target2) <= 0) {
						(*m).Death(target2);
						cout << "Monster" << target2 << " is dead.\n";
					}
					(*m).PrintMonster(target2);

					cout << "\n\n";
				}
				else {
					cout << "Attack Missed Due to Chance\n";
				}
		}

		if ((*p).GetIsAlive(3)) {
			cout << "Character 3, Enter Your Target Monster: \n";

			cin >> target3;
				if (((rand() % 100) + 1) > 15) {
					(*m).SetHealth(target3, (*p).GetPower(3));
					cout << "Character 3 attacked Monster " << target3 << "\n";
					cout << "Status of Monster " << target3 << " - \n";
					if ((*m).GetHealth(target3) <= 0) {
						(*m).Death(target3);
						cout << "Monster" << target3 << " is dead.\n";
					}
					(*m).PrintMonster(target3);
					cout << "\n\n";
				}
				else {
					cout << "Attack Missed Due to Chance\n";
				}
		}
		if ((*p).GetIsAlive(4)) {
			cout << "Character 4, Enter Your Target Monster: \n";

			cin >> target4;
			if (((rand() % 100) + 1) > 15) {
				(*m).SetHealth(target4, (*p).GetPower(4));
				cout << "Character 4 attacked Monster " << target4 << "\n";
				cout << "Status of Monster " << target4 << " - \n";
				if ((*m).GetHealth(target4) <= 0) {
					(*m).Death(target4);
					cout << "Monster" << target4 << " is dead.\n";
				}
				(*m).PrintMonster(target4);
				cout << "\n\n";
			}
				else {
					cout << "Attack Missed Due to Chance\n";
				}
		}
		
		if ((*p).GetIsAlive(5)) {

			cout << "Character 5, Enter Your Target Monster: \n";

			cin >> target5;
				if (((rand() % 100) + 1) > 15) {
					(*m).SetHealth(target5, (*p).GetPower(5));
					cout << "Character 5 attacked Monster " << target5 << "\n";
					cout << "Status of Monster " << target5 << " - \n";
					if ((*m).GetHealth(target5) <= 0) {
						(*m).Death(target5);
						cout << "Monster" << target5 << " is dead.\n";
					}
					(*m).PrintMonster(target5);
					cout << "\n\n";
				}
				else {
						cout << "Attack Missed Due to Chance\n";
				}
		}


		int count1 = 0;

		for (int i = 0; i < (*m).GetNumMonsters(); i++) {
			if ((*m).GetIsAlive(i + 1)) {
				count1++;
			}
		}

		if (count1 == 0) {
			monstersDead = true;
		}

		if (!monstersDead) {
			cout << "Monster Party Status: \n";

			cout << (*m) << "\n\n";

			if (rand() % 101 + 1 <= 50) {

				int randomAttack = rand() % 6 + 1;

				int power = (*m).GetCombinedPower();

				(*p).SetHealth(randomAttack, power);

				cout << "Character " << randomAttack << " was attacked by the monster party!\n";

				if ((*p).GetHealth(randomAttack) <= 0) {
					cout << "Character " << randomAttack << " is now dead.\n";
				}

			}
			else {
				cout << "Monster's attack missed by chance\n";
			}

			int count2 = 0;

			for (int i = 0; i < 5; i++) {
				if ((*p).GetIsAlive(i + 1)) {
					count2++;
				}
			}

			if (count2 == 0) {
				playersDead = true;
			}
		}

	} while (!monstersDead && !playersDead);

}

bool Board::CheckWin() {
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			if (board[i][j] == 'M' || board[i][j] == 'T') {
				return false; 
			}
		}
	}
	cout << "\n\nYou Win!!\n";
	return true;
}

bool Board::CheckLoss() {

	for (int i = 0; i < 5; i++) {
		if ((*p).GetIsAlive(i + 1)) {
			return false; 
		}
	}
	cout << "\n\nYou Lost!!\n";
	return true;
}



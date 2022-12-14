#include "Party.h"
#include <iostream>
#include <cstdlib>
using namespace std;


int main() {

	srand(time(0));

	Board b(5);

	b.setupEntrance();
	b.setupMonsters();
	b.setupTreasure();

	char action;

	cout << b;

	do {
		b.CheckStatus();
		cout << "\n\nEnter D to Display Party Status\n";
		cout << "Enter M to Move Party\n";
		cout << "Enter Q to Quit\n";
		cin >> action;

		switch (action) {
		case 'D':
			b.Display();
			break;

		case 'M':
			b.MoveParty();
			cout << b;
			break;
		}

	} while (action != 'Q' && !b.CheckWin() && !b.CheckLoss());


	return 0;
}
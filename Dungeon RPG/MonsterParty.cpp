#include "Party.h"
#include <cstdlib>
#include <iostream>

using namespace std;

MonsterParty::MonsterParty() {
	numMonsters = (rand() % 5) + 1;
	monsters = new Monster*[numMonsters];

	for (int i = 0; i < numMonsters; i++) {
		monsters[i] = new Monster;
	}
}

MonsterParty::~MonsterParty() {
	cout << "Deleting Monster Party...\n";
	for (int i = 0; i < numMonsters; i++) {
		delete[] monsters[i];
	}
	delete [] monsters;
}

void MonsterParty::SetRow(int r) {
	row = r;
}

void MonsterParty::SetCol(int c) {
	col = c;
}

int MonsterParty::GetRow() {
	return row;
}

int MonsterParty::GetCol() {
	return col;
}

int MonsterParty::GetNumMonsters() {
	return numMonsters;
}

void MonsterParty::PrintMonster(int index) {
	cout << (*monsters[index - 1]);
}

void MonsterParty::SetHealth(int index, int damage) {
	(*monsters[index - 1]).SetHealth((*monsters[index - 1]).GetHealth() - damage);
}

int MonsterParty::GetHealth(int index) {
	return (*monsters[index - 1]).GetHealth();
}

void MonsterParty::Death(int index) {
	(*monsters[index - 1]).SetIsAlive(false);

}

int MonsterParty::GetCombinedPower() {
	int allPower = 0;
	for (int i = 0; i < numMonsters; i++) {
		if ((*monsters[i]).GetIsAlive()) {
			allPower += (*monsters[i]).GetPower();
		}
	}
	return allPower;
}

ostream& operator<<(ostream& o, MonsterParty& m) {
	for (int i = 0; i < m.GetNumMonsters(); i++) {
		if ((*m.monsters[i]).GetIsAlive()) {
			o << "\nMonster #" << (i + 1) << "- " << (*m.monsters[i]) << "\n";
		}
		else {
			o << "\nMonster #" << (i + 1) << "is dead.\n";
		}
	}
	return o;
}

bool MonsterParty::GetIsAlive(int index) {
	return (*monsters[index - 1]).GetIsAlive();
}

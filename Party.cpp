#include "Party.h"
#include <iostream>
#include <cstdlib>

using namespace std;

Party::Party() {
	reward = 0;
	characters = new Character*[5];
	for (int i = 0; i < 5; i++) {
		characters[i] = new Character;
	}
}

Party::~Party() {
	cout << "Deleting Party...\n";
	for (int i = 0; i < 5; i++) {
		delete [] characters[i];
	}
	delete [] characters; 
}

void Party::CheckStatus() {
	int index = 0;

	for (int i = 0; i < numCharacters; i++) {
		if ((*characters[i]).GetHealth() <= 0) {
			index = i; 
			for (int j = index + 1; j < numCharacters; j++) {
				characters[j - 1] = characters[j];
			}
			numCharacters--;
		}
	}
}

int Party::GetPower(int index) {
	return (*characters[index - 1]).GetPower();
}

void Party::SetRow(int r) {
	row = r;
}

void Party::SetCol(int c) {
	col = c;
}

int Party::GetRow() {
	return row;
}

int Party::GetCol() {
	return col;
}

ostream& operator<<(ostream& o, Party& p) {
	for (int i = 0; i < 5; i++) {
		if ((*p.characters[i]).GetIsAlive()) {
			o << "\nCharacter #" << (i + 1) << "- " << (*p.characters[i]) << "\n";
		}
		else {
			o << "\nCharacter #" << (i + 1) << " is dead.\n";
		}
	}
    o << "\nParty Reward: " << p.reward;

	return o;
}

int Party::GetReward() {
	return reward; 
}

void Party::SetReward(int r) {
	reward += r;
}

void Party::SetTreasure(int t) {
	treasureCounter += t;
}

void Party::PrintCharacter(int index) {
	cout << (*characters[index - 1]);
}

int Party::GetTreasure() {
	return treasureCounter;
}

void Party::SetHealth(int index, int damage) {
	(*characters[index - 1]).SetHealth((*characters[index - 1]).GetHealth() - damage);
}

bool Party::GetIsAlive(int index) {
	return (*characters[index - 1]).GetIsAlive();
}

int Party::GetHealth(int index) {
	return (*characters[index - 1]).GetHealth();
}
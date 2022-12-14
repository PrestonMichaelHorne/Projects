#include "Party.h"
#include <iostream>
#include <cstdlib>

using namespace std;

Character::Character() {
	health = (rand() % 21) + 80;
	power = (rand() % 7) + 4;
	isAlive = true;
}

int Character::GetHealth() {
	return health;
}

void Character::SetHealth(int h) {
	health = h;
}

int Character::GetPower() {
	return power;
}

bool Character::GetIsAlive() {
	return isAlive;
}

void Character::SetIsAlive(bool a) {
	isAlive = a;
}

ostream& operator<<(ostream& o, Character& c) {
	o << "Health: " << c.GetHealth() << " Power: " << c.GetPower();
	return o;
}
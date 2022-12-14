#include "Party.h"
#include <iostream>
#include <cstdlib>

using namespace std;

Monster::Monster() {
	health = (rand() % 16) + 15;
	power = (rand() % 6) + 1;
	isAlive = true;
}

void Monster::SetHealth(int h) {
	health = h;
}

int Monster::GetHealth() {
	return health;
}

int Monster::GetPower() {
	return power;
}

bool Monster::GetIsAlive() {
	return isAlive;
}

void Monster::SetIsAlive(bool a) {
	isAlive = a;
}

ostream& operator<<(ostream& o, Monster& m) {
	o << "Health : " << m.GetHealth() << " Power : " << m.GetPower();
}


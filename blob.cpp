#include <iostream>
#include <cstdlib>
#include "blob.h"

using namespace std;

Blob::Blob() {

   Health = 100;
   Power = 10;
   isAlive = true;

}

Blob::Blob(char c) {
	Health = 100;
	Power = 10;
	Color = c;
	isAlive = true;
}

Blob::Blob(int h, int p, char c) {
   
   Health = h;
   Power = p;
   Color = c;
   isAlive = true;

}

void Blob::Spawn() {
	xCoord = (rand() % 10) + 1;
	yCoord = (rand() % 10) + 1;
}


void Blob::MoveNorth() {
	yCoord++;
}

void Blob::MoveSouth() {

	yCoord--;
}

void Blob::MoveEast() {

	xCoord++;

}

void Blob::MoveWest() { 

	xCoord--;
	
}

int Blob::GetXCoord() {
	return xCoord;
}

void Blob::SetXCoord(int x) {
	xCoord = x;
}

int Blob::GetYCoord() {
	return yCoord;
}

void Blob::SetYCoord(int y) {
	yCoord = y;
}

char Blob::GetColor() {
	return Color;
}

int Blob::GetHealth() {
	return Health; 
}

int Blob::GetPower() {
	return Power; 
}

void Blob::SetIsAlive(bool b) {
	isAlive = b;
	xCoord = 0;
	yCoord = 0;
}

bool Blob::GetIsAlive() {
	return isAlive;
}

void Blob::SetHealth(int h) {
    	Health = h;
}

ostream& operator<<(ostream& o, Blob b) {
	if (b.isAlive) {
		o << "(" << b.xCoord << ", " << b.yCoord << ")";
	}
	if (!b.isAlive) {
		o << "This Blob has Died.";
	}
	return o; 
}



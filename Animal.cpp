#include "Animal.h"

#include <iostream>
#include <string>

using namespace std;


void Dog::MakeSound() {
	cout << "woof";
}

void Cat::MakeSound() {
	cout << "meow";
}

void Pig::MakeSound() {
	cout << "oink";
}

void Cow::MakeSound() {
	cout << "moo";
}

Ranch::Ranch() {
	currentSize = 0;
	maxSize = 4;
	ranch = new Animal*[maxSize];
}

Ranch::~Ranch() {
	delete[] ranch;
}

Ranch::Ranch(const Ranch& r) {
	currentSize = r.currentSize;
	maxSize = r.maxSize;

	ranch = new Animal*[maxSize];
	for (int i = 0; i < currentSize; i++) {
		ranch[i] = r.ranch[i];
	}
}

void Ranch::AddDog() {
	Dog* d = new Dog;
	ranch[currentSize] = d;
	currentSize++;
	if (currentSize == maxSize) {
		Grow();
	}
}

void Ranch::AddCat() {
	Cat* c = new Cat;
	ranch[currentSize] = c;
	currentSize++;
	if (currentSize == maxSize) {
		Grow();
	}
}

void Ranch::AddPig() {
	Pig* p = new Pig;
	ranch[currentSize] = p;
	currentSize++;
	if (currentSize == maxSize) {
		Grow();
	}
}

void Ranch::AddCow() {
	Cow* c = new Cow;
	ranch[currentSize] = c;
	currentSize++;
	if (currentSize == maxSize) {
		Grow();
	}
}

void Ranch::Grow() {
	maxSize = currentSize + 4;
	Animal** temp = new Animal * [maxSize];

	for (int i = 0; i < currentSize; i++) {
		temp[i] = ranch[i];
	}

	delete[] ranch;

	ranch = temp;
}



void Ranch::Menu() {

	string input;

	do {

		cout << "Enter 'dog', 'cat', 'pig', 'cow', 'print', or 'quit' : ";
		cin >> input;

		if (input == "dog") {
			AddDog();
		}

		else if (input == "cat") {
			AddCat();
		}

		else if (input == "pig") {
			AddPig();
		}

		else if (input == "cow") {
			AddCow();
		}
		else if (input == "print") {
			Print();
		}


	} while (input != "quit");
}

void Ranch::Print() {
	cout << "\n";
	for (int i = 0; i < currentSize; i++) {
		ranch[i]->MakeSound();
		cout << "\n";
	}

	cout << "\n";
}

void Ranch::operator=(const Ranch& r) {
	currentSize = r.currentSize;
	maxSize = r.maxSize;

	ranch = new Animal * [maxSize];
	for (int i = 0; i < currentSize; i++) {
		ranch[i] = r.ranch[i];
	}
}


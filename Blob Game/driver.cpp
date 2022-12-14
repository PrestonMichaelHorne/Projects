#include "blob.h"
#include <cstdlib>
#include <iostream>

using namespace std;

int numBlobs = 8; // starts at 8

const int MAX_BLOBS = 14; // max #, adding possible combinations

typedef Blob BlobList[MAX_BLOBS];

void PrintBlueStats(BlobList& blobs);
void PrintRedStats(BlobList& blobs);
void BlobMove(BlobList& blobs, int blobNum);
void BlobAttack(BlobList& blobs, int blobNum);
Blob operator+(Blob, Blob);

int main() {
	BlobList blobs;

	srand(time(0));

	// blue team 
	for (int i = 0; i < 4; i++) {
		blobs[i] = Blob('b');
		blobs[i].Spawn();
	}

	// red team
	for (int i = 4; i < 8; i++) {
		blobs[i] = Blob('r');
		blobs[i].Spawn();
	}
	
	//check if blobs are all on separate squares  
	for (int i = 0; i < numBlobs; i++) {

		for (int j = i + 1; j < numBlobs; j++) {
			if (blobs[i].GetXCoord() == blobs[j].GetXCoord() && blobs[i].GetYCoord() == blobs[j].GetYCoord()) {
				int tempX = blobs[i].GetXCoord();
				int tempY = blobs[i].GetYCoord();
				while (blobs[i].GetXCoord() == tempX && blobs[i].GetYCoord() == tempY) {
					blobs[i].Spawn();
				}
				j = i + 1;
			}
		}

		for (int j = i - 1; j >= 0; j--) {
			if (blobs[i].GetXCoord() == blobs[j].GetXCoord() && blobs[i].GetYCoord() == blobs[j].GetYCoord()) {
				int tempX = blobs[i].GetXCoord();
				int tempY = blobs[i].GetYCoord();
				while (blobs[i].GetXCoord() == tempX && blobs[i].GetYCoord() == tempY) {
					blobs[i].Spawn();
				}
				j = i - 1;
			}
		}

	}

	char action; 
	bool isEnd = false;
	int numBlue = 0;
	int numRed = 0;
	do {

		int blobNum;

		PrintBlueStats(blobs);

		cout << "\nEnter Your Blob # to Play: ";

		cin >> blobNum;

		cout << "Enter m to move or a to attack: ";
		cin >> action;

		if (action == 'm') {
			BlobMove(blobs, blobNum);
		}

		else if (action == 'a') {
			BlobAttack(blobs, blobNum);
		}

		numBlue = 0;
		numRed = 0;
		for (int i = 0; i < numBlobs; i++) {
			if (blobs[i].GetColor() == 'b' && blobs[i].GetIsAlive()) {
				numBlue++;
			}
			else if (blobs[i].GetColor() == 'r' && blobs[i].GetIsAlive()) {
				numRed++;
			}
		}

		if (numRed == 0 || numBlue == 0) {
			isEnd = true;
		}

		if (action != 'q' && !isEnd) {

			PrintRedStats(blobs);

			cout << "\nEnter Your Blob # to Play: ";

			cin >> blobNum;

			cout << "Enter m to move or a to attack: ";

			cin >> action;

			if (action == 'm') {
				BlobMove(blobs, blobNum);
			}

			else if (action == 'a') {
				BlobAttack(blobs, blobNum);
			}			

			numRed = 0;
			numBlue = 0;

			for (int i = 0; i < numBlobs; i++) {
				if (blobs[i].GetColor() == 'b' && blobs[i].GetIsAlive()) {
					numBlue++;
				}
				else if (blobs[i].GetColor() == 'r' && blobs[i].GetIsAlive()) {
					numRed++;
				}
			}

			if (numRed == 0 || numBlue == 0) {
				isEnd = true;
			}
		}

	} while (action != 'q' && !isEnd);
	
	if (numRed == 0) {
		cout << "The Blue Team has Won!!!\n";
	}
	else if (numBlue == 0) {
		cout << "The Red Team has Won!!!\n";
	}

}

void PrintBlueStats(BlobList& blobs) {
	cout << "\nMy Blobs (Blue Team) -\n";
    for(int i = 0; i < numBlobs; i++) {
			if (blobs[i].GetColor() == 'b' && blobs[i].GetIsAlive()) {
				cout << "Blob " << (i + 1) << ": " << blobs[i] << endl;
			}
		}

	cout << "Opponent's Blobs (Red Team) -\n";

	for(int i = 0; i < numBlobs; i++) {
			if (blobs[i].GetColor() == 'r' && blobs[i].GetIsAlive()) {
				cout << "Blob " << (i + 1) << ": " << blobs[i] << endl;
			}
        }
}

void PrintRedStats(BlobList& blobs) {
	cout << "\nMy Blobs (Red Team) -\n";
	for (int i = 0; i < numBlobs; i++) {
		if (blobs[i].GetColor() == 'r' && blobs[i].GetIsAlive()) {
			cout << "Blob " << (i + 1) << ": " << blobs[i] << endl;
		}
	}

	cout << "Opponent's Blobs (Blue Team) -\n";

	for (int i = 0; i < numBlobs; i++) {
		if (blobs[i].GetColor() == 'b' && blobs[i].GetIsAlive()) {
			cout << "Blob " << (i + 1) << ": " << blobs[i] << endl;
		}
	}
}

Blob operator+(Blob a, Blob b) {
	
	int cPower = 0; 
	if (a.GetPower() >= b.GetPower()) {
		cPower = a.GetPower() + 2;
	}
	else if (a.GetPower() < b.GetPower()) {
		cPower = b.GetPower() + 2;
	}

	Blob c = Blob(a.GetHealth() + b.GetHealth(), cPower, a.GetColor());
	
	int aXCoord = a.GetXCoord();
	int aYCoord = a.GetYCoord();
	c.SetXCoord(aXCoord);
	c.SetYCoord(aYCoord);
	return c; 
}

void BlobMove(BlobList& blobs, int blobNum) {
	char direction;
	cout << "Enter n for north, s for south, e for east, and w for west: ";
	cin >> direction;

	bool isOutOfBounds = false;

	if (direction == 'n') {
		if (blobs[blobNum - 1].GetYCoord() < 10) {
			blobs[blobNum - 1].MoveNorth();
		}
		else {
			isOutOfBounds = true;
		}
	}
	else if (direction == 's') {
		if (blobs[blobNum - 1].GetYCoord() > 1) {
			blobs[blobNum - 1].MoveSouth();
		}
		else {
			isOutOfBounds = true;
		}

	}
	else if (direction == 'e') {
		if (blobs[blobNum - 1].GetXCoord() < 10) {
			blobs[blobNum - 1].MoveEast();
		}
		else {
			isOutOfBounds = true;
		}

	}
	else if (direction == 'w') {

		if (blobs[blobNum - 1].GetXCoord() > 1) {
			blobs[blobNum - 1].MoveWest();
		}
		else {
			isOutOfBounds = true;
		}

	}

	if (isOutOfBounds) {
		cout << "\nOut of Bounds Error, Please Try Again Next Time.\n";
	}

	bool isAdded = false;

	for (int i = 0; i < numBlobs; i++) {
		if ((blobNum - 1) != i && blobs[i].GetIsAlive()) {
			if (blobs[blobNum - 1].GetXCoord() == blobs[i].GetXCoord() && blobs[blobNum - 1].GetYCoord() == blobs[i].GetYCoord()) {
				if (blobs[blobNum - 1].GetColor() != blobs[i].GetColor()) {
					if (direction == 'n') {
						blobs[blobNum - 1].MoveSouth();
					}
					else if (direction == 's') {
						blobs[blobNum - 1].MoveNorth();
					}
					else if (direction == 'e') {
						blobs[blobNum - 1].MoveWest();
					}
					else if (direction == 'w') {
						blobs[blobNum - 1].MoveEast();
					}

					if (blobs[i].GetColor() == 'b') {
						cout << "\nThat Square is Taken By the Blue Team, Please Try Again Next Time.\n";
						break;
					}

					else if (blobs[i].GetColor() == 'r') {
						cout << "\nThat Square is Taken By the Red Team, Please Try Again Next Time.\n";
						break;
					}

				}
			else if (blobs[i].GetColor() == blobs[blobNum - 1].GetColor()) {
					blobs[numBlobs] = blobs[i] + blobs[blobNum - 1];
					blobs[i].SetIsAlive(false);
					blobs[blobNum - 1].SetIsAlive(false);
					cout << "\nBlob #" << blobNum << " + Blob #" << i + 1 << " = Blob #" << numBlobs + 1 << "\n";
					isAdded = true;
					break;
				}
			}
		}
	}

	if (isAdded && numBlobs < 14) {
		numBlobs++;
	}
}

void BlobAttack(BlobList& blobs, int blobNum) {

	char direction;

	cout << "Enter Direction of Attack (n, s, e, or w): ";

	cin >> direction;

	bool isAttack = false;

	bool isOwnTeam = false;

	for (int i = 0; i < numBlobs; i++) {
		if (blobs[blobNum - 1].GetColor() != blobs[i].GetColor()) {
			if (direction == 'n') {
				if ((blobs[blobNum - 1].GetYCoord() + 1) == blobs[i].GetYCoord() && (blobs[blobNum - 1].GetXCoord()) == blobs[i].GetXCoord()) {
					isAttack = true;
				}
			}

			else if (direction == 's') {
				if (blobs[blobNum - 1].GetYCoord() - 1 == (blobs[i].GetYCoord()) && (blobs[blobNum - 1].GetXCoord()) == blobs[i].GetXCoord()) {
					isAttack = true;
				}
			}
			else if (direction == 'e') {
				if ((blobs[blobNum - 1].GetYCoord()) == blobs[i].GetYCoord() && (blobs[(blobNum - 1)].GetXCoord()) + 1 == (blobs[i].GetXCoord())) {
					isAttack = true;
				}
			}

			else if (direction == 'w') {
				if ((blobs[blobNum - 1].GetYCoord()) == blobs[i].GetYCoord() && (blobs[blobNum - 1].GetXCoord()) - 1 == (blobs[i].GetXCoord())) {
					isAttack = true;
				}
			}

			if (isAttack) {
				blobs[i].SetHealth((blobs[i].GetHealth()) - (blobs[blobNum - 1].GetPower()));
				cout << "\nBlob #" << blobNum << " did " << blobs[blobNum - 1].GetPower() << " damage to Blob #" << i + 1;
				if (blobs[i].GetHealth() <= 0) {
					cout << "\nBlob #" << i + 1 << " is now dead." << "\n\n";
					blobs[i].SetIsAlive(false);
				}
				else {
					cout << "\nThe Health of Blob #" << i + 1 << " is now " << blobs[i].GetHealth() << "\n";
				}
				break;
			}
		}
		else if (blobs[blobNum - 1].GetColor() == blobs[i].GetColor()) {
			if (direction == 'n') {
				if ((blobs[blobNum - 1].GetYCoord() + 1) == blobs[i].GetYCoord() && (blobs[blobNum - 1].GetXCoord()) == blobs[i].GetXCoord()) {
					isOwnTeam = true;
				}
			}

			else if (direction == 's') {
				if (blobs[blobNum - 1].GetYCoord() - 1 == (blobs[i].GetYCoord()) && (blobs[blobNum - 1].GetXCoord()) == blobs[i].GetXCoord()) {
					isOwnTeam = true;
				}
			}
			else if (direction == 'e') {
				if ((blobs[blobNum - 1].GetYCoord()) == blobs[i].GetYCoord() && (blobs[(blobNum - 1)].GetXCoord()) + 1 == (blobs[i].GetXCoord())) {
					isOwnTeam = true;
				}
			}

			else if (direction == 'w') {
				if ((blobs[blobNum - 1].GetYCoord()) == blobs[i].GetYCoord() && (blobs[blobNum - 1].GetXCoord()) - 1 == (blobs[i].GetXCoord())) {
					isOwnTeam = true;
				}
			}

			if (isOwnTeam) {
				cout << "\nThis Square is Taken by Your Own Team, Please Try Again Next Time\n";
				break;
			}
		}
	}
	
	if (!isAttack && !isOwnTeam) {
		cout << "\nAttack Failed: Square is Empty.\n";
	}
}


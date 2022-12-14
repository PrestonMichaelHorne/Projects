#include <iostream>

using namespace std;

class Character {
	friend ostream& operator<<(ostream&, Character&);

	public:
		Character();
		int GetHealth();
		int GetPower();
		void SetIsAlive(bool);
		bool GetIsAlive();
		void SetHealth(int);

	private:
		int health; 
		int power; 
		bool isAlive;
};

class Monster {
	friend ostream& operator<<(ostream&, Monster&);

	public:
		Monster();
		int GetHealth();
		int GetPower();
		void SetHealth(int);
		void SetIsAlive(bool);
		bool GetIsAlive();
	private:
		int health;
		int power;
		int reward;
		bool isAlive;
};

class MonsterParty {
	friend ostream& operator<<(ostream&, MonsterParty&);

	public:
		MonsterParty();
		~MonsterParty();
		int GetReward();
		void SetRow(int);
		void SetCol(int);
		int GetRow();
		int GetCol();
		void SetHealth(int, int);
		int GetHealth(int);
		int GetNumMonsters();
		void PrintMonster(int);
		Monster** monsters;
		void Death(int);
		int GetCombinedPower();
		bool GetIsAlive(int);

	private:
		
		int numMonsters;
		int row; 
		int col;
};


class Party {

	friend ostream& operator<<(ostream&, Party&);

	public:
		Party();
		~Party();
		Party(const Party&);
		void operator=(const Party&);
		void Grow();
		void CheckStatus();
		void SetRow(int);
		void SetCol(int);
		int GetRow();
		int GetCol();
		int GetReward();
		void SetReward(int);
		int GetPower(int);
		int GetTreasure();
		void SetTreasure(int);
		void SetHealth(int, int);
		bool GetIsAlive(int);
		int GetHealth(int);
		void PrintCharacter(int);

	private:
		int reward;
		int treasureCounter;
		int row;
		int col;
		Character** characters; 
		int numCharacters;
};

class Treasure {
public:
	Treasure();
	int GetReward();
	void SetReward(int r);
	void SetRow(int);
	void SetCol(int);
	int GetRow();
	int GetCol();
	void TakeTreasure();
	void Combat();
private:
	int reward;
	int row;
	int col;
};

class Board {
	friend ostream& operator<<(ostream&, const Board&);

public:
	Board(int);
	~Board();
	char** board;
	void setupEntrance();
	void setupMonsters();
	void setupTreasure();
	void MoveParty();
	void Display();
	void CheckStatus();
	void Combat();
	bool CheckWin();
	bool CheckLoss();

private:
	int size;
	Party* p;
	MonsterParty* m;
	int** t;
	int numM;
	int numT;
};


